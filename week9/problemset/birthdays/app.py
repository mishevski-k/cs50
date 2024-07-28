import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    stocks = db.execute("select * from portfolios where user_id = ? ", session['user_id'])
    user = db.execute("select * from users where id = ? ", session["user_id"])[0]
    grandTotal = user["cash"]
    for stock in stocks:
        quote = lookup(stock['symbol'])
        if (quote):
            stock["price"] = quote["price"]
            stock["total"] = int(quote["price"]) * int(stock["shares"])
            grandTotal += stock["total"]
    return render_template("index.html", stocks=stocks, user=user, grandTotal=grandTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Symbol for stock is required", 400)

        if not request.form.get("shares"):
            return apology("Ammount of stocks is required", 400)

        shares = request.form.get("shares")

        if not shares.isdigit():
            return apology("Wrong amount of shares provided", 400)
        shares = int(shares)

        if shares <= 0:
            return apology("Cannot buy 0 shares")

        stock = lookup(request.form.get("symbol"))

        if not stock:
            return apology("Stock not found", 400)

        rows = db.execute("Select * from users where id = ? ", session["user_id"])

        if not rows or len(rows) != 1:
            return apology("A error occured, pls try again later", 400)
        user = rows[0]
        if (stock['price'] * shares) > user['cash']:
            return apology("Insufficent funds", 400)

        existingShares = db.execute(
            "SELECT * FROM portfolios WHERE user_id = ? AND symbol = ? ", user['id'], stock['symbol'].upper())

        if len(existingShares) != 1:
            db.execute("insert into portfolios (user_id, symbol, shares) values (?, ?, ?) ",
                       user['id'], stock['symbol'].upper(), shares)
        else:
            existingShare = existingShares[0]
            db.execute("update portfolios set shares = ? where user_id = ? and symbol = ? ", int(
                existingShare['shares']) + shares, user['id'], stock['symbol'].upper())

        db.execute("update users set cash = ? where id = ? ", int(
            user["cash"]) - int((stock['price'] * shares)), user["id"])
        db.execute("insert into transactions (user_id, symbol, transaction_type, shares, price, timestamp ) values (?, ?, ?, ?, ?, ? ) ",
                   user["id"], stock["symbol"].upper(), "BUY", shares, stock["price"], datetime.now().strftime('%Y-%m-%d %H:%M:%S'))

        return redirect("/")
    else:
        return render_template("buy.html", symbol=request.args.get("symbol", ""))


@app.route("/history")
@login_required
def history():
    rows = db.execute(
        "select * from transactions where user_id = ? order by timestamp desc ", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == 'POST':

        if not request.form.get("symbol"):
            return apology("Symbol for stock is required", 400)

        data = lookup(request.form.get("symbol"))

        if not data:
            return apology("Quote not found")
        return render_template("quoted.html", quote=data)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == 'POST':
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation", 400):
            return apology("must confirm password")

        # Ensure password and confirmation are the same
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation must match")

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if (len(rows) > 0):
            return apology("username is already taken")

        db.execute("insert into users (username, hash) values (?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Symbol must be providede", 400)
        symbol = request.form.get("symbol").upper()
        if not request.form.get("shares"):
            return apology("Amount of shares must be providede", 400)
        shares = int(request.form.get("shares"))
        if shares < 0:
            return apology("Amount of shares is invalid", 400)

        stock = db.execute(
            "select * from portfolios where user_id = ? and symbol = ? ", session["user_id"], symbol)
        user = db.execute("select * from users where id = ? ", session["user_id"])[0]

        if len(stock) != 1:
            return apology("User does not hold that stock", 400)
        elif stock[0]["shares"] < shares:
            return apology("User does not hold that many shares", 400)

        quote = lookup(symbol)

        if (stock[0]["shares"] - shares == 0):
            db.execute("delete from portfolios where user_id = ? and symbol = ? ",
                       user["id"], symbol.upper())
        else:
            db.execute("update portfolios set shares = ? where user_id = ? and symbol = ? ",
                       stock[0]["shares"] - shares, user["id"], symbol.upper())

        db.execute("update users set cash = ? where id = ? ", int(
            user["cash"] + quote["price"] * shares), session["user_id"])
        db.execute("insert into transactions (user_id, symbol, transaction_type, shares, price, timestamp ) values (?, ?, ?, ?, ?, ? ) ",
                   user["id"], symbol.upper(), "SELL", shares, quote["price"], datetime.now().strftime('%Y-%m-%d %H:%M:%S'))

        return redirect("/")
    else:

        stocks = db.execute("select * from portfolios where user_id = ? ", session["user_id"])

        return render_template("sell.html", stocks=stocks, symbol=request.args.get("symbol", None))

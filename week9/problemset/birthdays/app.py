import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

def insertBirthday(name, month, day):
    db.execute("insert into birthdays (name, month, day) values(?, ?, ?)", name, month, day)

def updateBirthday(id, name, month, day):
    db.execute("update birthdays set name = ?, month = ?, day = ? where id = ?", name, month, day, id)

def deleteBirthday(id):
    db.execute("delete from birthdays where id = ?", id)

def getBirthdays():
    return db.execute("select * from birthdays")

def getBirthday(id):
    birthdays = db.execute("select * from birthdays where id = ?", id)
    
    if(len(birthdays) > 0):
        return birthdays[0]
    else:
        return None

def validateBirthday():
    errors = []

    name =  request.form.get("name")
    if(not name):
        errors.append("Name is required")
    month = request.form.get("month")
    if(not month):
        errors.append("Month is required")
    day = request.form.get("day")
    if(not day):
        errors.append("Day is required")

    return errors
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        errors = validateBirthday()

        if(len(errors) > 0):
            return render_template("error.html", errors=errors)

        insertBirthday(request.form.get("name"), request.form.get("month"), request.form.get("day"))    

        return redirect("/")

    else:
        birthdays = getBirthdays()
        return render_template("index.html", birthdays=birthdays)
    
@app.route("/edit/", methods=["GET", "POST"])
def edit():
    if(request.method == "POST"):
        errors = validateBirthday()
            
        if(len(errors) > 0):
            return render_template("error.html", errors=errors)
            
        updateBirthday(request.form.get("id"), request.form.get("name"), request.form.get("month"), request.form.get("day"))
            
        return redirect("/")
    else:
        id = request.args.get("id")
        birthday = getBirthday(id)
        print(birthday)
        if(birthday):
            return render_template("edit.html", birthday=birthday)
        else:
            return render_template("error.html", errorMessage=f"Could not find birthday with id: {id}")
        
@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    
    if(not id):
        return render_template("error.html", errorMessage="Could not find birthday id to delete")
    
    deleteBirthday(id)
    
    return redirect("/")

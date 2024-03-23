def main():
    change = get_change()

    total_coins = 0

    if change >= 25:
        quarters = calculate_coins_amount(25, change)
        change %= (quarters * 25)
        total_coins += quarters

    if change >= 10:
        dimes = calculate_coins_amount(10, change)
        change %= (dimes * 10)
        total_coins += dimes

    if change >= 5:
        nickels = calculate_coins_amount(5, change)
        change %= (nickels * 5)
        total_coins += nickels

    if change >= 1:
        pennies = calculate_coins_amount(1, change)
        change %= pennies
        total_coins += pennies

    print(total_coins)


def calculate_coins_amount(coin_value, amount):
    return int(amount / coin_value)


def get_change():
    while True:
        change = get_float("Change: ")

        if change > 0:
            break

    return change * 100


def get_float(prompt):
    while True:
        try:
            return float(input(prompt))
        except ValueError:
            print("Not a Number")


main()

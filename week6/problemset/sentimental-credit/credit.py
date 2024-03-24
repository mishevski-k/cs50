def main():
    while True:
        card_number = get_int("Number: ")

        if (card_number >= 1):
            break

    total_sum = calculate_first_line_sum(card_number) + calculate_second_lin_sum(card_number)

    isValid = (total_sum % 10) == 0

    print_validation_message(isValid, card_number)


def print_validation_message(isValid, number):
    if isValid:
        card_provider = ""
        start_numbers = get_card_start_digits(number)
        card_length = len(str(number))

        if start_numbers in [34, 37, 15] and card_length == 15:
            card_provider = "AMEX"
        elif start_numbers in [51, 52, 53, 54, 55] and card_length == 16:
            card_provider = "MASTERCARD"
        elif int(start_numbers / 10) == 4 and card_length in [13, 16]:
            card_provider = "VISA"
        else:
            card_provider = "INVALID"

        print(card_provider)
    else:
        print("INVALID")


def calculate_first_line_sum(number):
    sum = 0

    while number >= 10:
        number = int(number / 10)
        every_other_digit = (number % 10) * 2

        if every_other_digit >= 10:
            sum += (every_other_digit % 10) + (int(every_other_digit / 10))
        else:
            sum += every_other_digit

        number = int(number / 10)

    return sum


def calculate_second_lin_sum(number):
    sum = 0

    while number >= 10:
        sum += (number % 10)
        number = int(number / 100)

    if number > 0 and number < 10:
        sum += number

    return sum


def get_card_start_digits(number):
    while number > 100:
        number = int(number / 10)

    return number


def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Not a Numelic Value")


main()

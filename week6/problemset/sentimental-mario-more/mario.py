def main():

    height = get_height()

    print_pyramide(height)


def print_pyramide(height):
    for i in range(height):
        print_row(height - i - 1, i + 1)


def print_row(spaces, blocks):
    print(" " * spaces + "#" * blocks + "  " + "#" * blocks)


def get_height():
    while True:

        height = get_int("Height: ")

        if height > 0 and height <= 8:
            break

        print("Height must be a positive integer less or equal to 8")

    return height


def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Not an Integer")


main()

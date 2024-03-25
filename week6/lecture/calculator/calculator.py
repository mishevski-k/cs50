# import cs50

# x = cs50.get_int("x: ")
# y = cs50.get_int("y: ")

# print(x + y)

def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Not an integer")

def main():
    x = get_int("x: ")
    y = get_int("y: ")

    print(x + y)

main()
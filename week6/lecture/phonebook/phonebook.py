# names = ["Carter", "David", "John"]

# name = input("Name: ")

# for n in names:
#     if name == n:
#         print("Found")
#         break
# else:
#     print("Not found")

# if name in names:
#     print("Found")
# else:
#     print("Not found")

# people = [
#     {
#         "name": "Carter", "number": "+1-617-495-1000"
#     },
#     {
#         "name": "David", "number": "+1-617-495-1000"
#     },
#     {
#         "name": "John", "number": "+1-949-468-2750"
#     },
# ]

people = {
    "Carter": "+1-617-495-1000",
    "David": "+1-617-495-1000",
    "John": "+1-949-468-2750",
}

name = input("Names: ")

# for person in people:
#     if person["name"] == name:
#         print(f"Found {person['number']}")
#         break
# else:
#     print("Not found")

if name in people:
    print(f"Found {people[name]}")
else:
    print("Not found")
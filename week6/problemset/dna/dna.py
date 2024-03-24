import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna [database] [sequances]")

    database_headers = []
    database = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        database_headers = reader.fieldnames
        for row in reader:
            database.append(row)

    sequance_file = open(sys.argv[2], "r")
    sequance = sequance_file.read()

    sequance_matches = []

    counter = 1
    header_lenght = len(database_headers)
    while counter < header_lenght:
        str = database_headers[counter]

        match = longest_match(sequance, str)

        sequance_matches.append({"STR": str, "value": match})

        counter += 1

    database_length = len(database)

    name = ""

    for person in range(database_length):
        if check_match(database[person], sequance_matches):
            return print(database[person]["name"])
    else:
        print("No match")

    return


def check_match(person, sequance_matches):
    for i in sequance_matches:
        if int(person[i['STR']]) != i["value"]:
            return False
    else:
        return True


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

import csv
import sys

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3 :
        return


    # TODO: Read database file into a variable

    subsequence = []
    with open(f"{sys.argv[1]}", 'r') as file:
        reader = csv.DictReader(file)
        for row in reader :
            subsequence.append(row)


    # TODO: Read DNA sequence file into a variable

    with open(f"{sys.argv[2]}", encoding="utf-8") as f:
        sequence = f.read()


    # TODO: Find longest match of each STR in DNA sequence

    to_check_obj = {}

    for key in subsequence[0].keys():
        if key == 'name':
            continue
        match_count = longest_match(sequence, key)
        to_check_obj[key] = match_count


    # TODO: Check database for matching profiles

    for row in subsequence:
        found = True

        for key in row.keys():
            if key == 'name': continue
            if int(row[key]) != to_check_obj[key]:
                found = False
                break

        if found :
            print(row['name'])
            return

    print('No match')
    return


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

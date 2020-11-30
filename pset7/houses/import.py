from cs50 import SQL
import csv
import sys

# Open database
db = SQL("sqlite:///students.db")

# Read CSV file name from command-line
csvFile = sys.argv[1]

# Open CSV file
with open(csvFile, "r") as characters:

    # Create DictReader
    reader = csv.DictReader(characters)

    # Iterate over CV file
    for row in reader:

        # Split full name into first, middle, last names and create array for them
        fullName = row["name"].split()

        # If middle name
        if len(fullName) == 3:
            firstName = fullName[0]
            middleName = fullName[1]
            lastName = fullName[2]

        # If no middle name
        elif len(fullName) == 2:
            firstName = fullName[0]
            middleName = None
            lastName = fullName[1]

        # Set variables for house and birth
        house = row["house"]
        birth = int(row["birth"])

        # Insert show
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?);", 
                   (firstName, middleName, lastName, house, birth))

from cs50 import SQL
import sys

# Check number of args
if len(sys.argv) != 2:
    sys.exit("Usage: python roster.py house")

# Open database
db = SQL("sqlite:///students.db")

# Read requested data
sql = "SELECT * FROM students WHERE house = ? ORDER BY last, first"
characters = db.execute(sql, sys.argv[1])

# Print names according to house
for character in characters:
    if character["middle"] == None:
        print("{} {}, born {}".format(character["first"], character["last"], character["birth"]))
    else:
        print("{} {} {}, born {}".format(character["first"], character["middle"], character["last"], character["birth"]))
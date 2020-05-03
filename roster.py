from cs50 import SQL
from sys import exit, argv

if len(argv) != 2:
    exit(1)

house = argv[1]

db = SQL("sqlite:///students.db")

houses = db.execute("SELECT first, middle, last, birth , house FROM students WHERE house = :house ORDER BY last, first", house=house)
for row in houses:
    print(row["first"], end=" ")
    if row["middle"] != None:
        print(row["middle"], end=" ")
    print(row["last"],",", end=" ", sep="")
    print("born", row["birth"])
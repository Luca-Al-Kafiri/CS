
from sys import argv, exit
from cs50 import SQL
import csv

if len(argv) != 2:
    exit(1)

db = SQL("sqlite:///students.db")

with open(argv[1], "r") as houses:
    reader = csv.DictReader(houses)
    for row in reader:
        name = row["name"].split( )
        if len(name) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)", name[0], name[1], row["house"], row["birth"])
        elif len(name) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", name[0], name[1], name[2], row["house"], row["birth"])
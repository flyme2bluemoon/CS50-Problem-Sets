import cs50
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python3 import.py characters.csv")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

the_characters = []

with open(argv[1], "r") as the_characters_csv:
    the_characters_reader = csv.DictReader(the_characters_csv)
    for row in the_characters_reader:
        the_characters.append(row)

the_current_id = 1
for i in the_characters:
    the_current_name = i["name"].split(" ")
    the_current_house = i["house"]
    the_current_birth = int(i["birth"])
    if len(the_current_name) == 2:
        db.execute("INSERT INTO students VALUES (?, ?, ?, ?, ?, ?);", the_current_id, the_current_name[0], None, the_current_name[1], the_current_house, the_current_birth)
    else:
        db.execute("INSERT INTO students VALUES (?, ?, ?, ?, ?, ?);", the_current_id, the_current_name[0], the_current_name[1], the_current_name[2], the_current_house, the_current_birth)
    the_current_id += 1
    print(the_current_id, the_current_name, the_current_house, the_current_birth)

# print(the_characters)
import cs50
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python3 roster.py house")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

the_result = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first;", argv[1])

for i in the_result:
    if i["middle"] != None:
        print(i["first"], i["middle"], i["last"], end="")
    else:
        print(i["first"], i["last"], end="")
    print(", born", i["birth"])
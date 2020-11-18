from sys import argv, exit
import csv

# python3 dna.py databases/large.csv sequences/1.txt

if (len(argv) != 3):
    print("Usage: python3 dna.py data.csv sequence.txt")
    exit(1)

# print(argv)

the_sequence = ""
the_database = []
the_max_count = {}

# get the_title row
with open(argv[1]) as the_database_file:
    the_title = next(csv.reader(the_database_file))
    the_title.remove("name")

# load the_database_file into memory
with open(argv[1]) as the_database_file:
    the_database_reader = csv.DictReader(the_database_file)
    for row in the_database_reader:
        the_database.append(row)

# load the_sequence_file into memory
with open(argv[2]) as the_sequence_file:
    the_sequence = the_sequence_file.read().rstrip("\n")

# count consecutive repeats of str in dna
for i in the_title:
    the_max_count[i] = 0
    the_current_count = 0
    j = 0
    n = len(the_sequence) - len(i)
    while (j < n):
        if the_sequence[j:j + len(i)] == i:
            the_current_count += 1
            if the_current_count > the_max_count[i]:
                the_max_count[i] = the_current_count
            j = j + len(i)
        else:
            the_current_count = 0
            j += 1

# find and print the person
name = "No match"
for i in the_database:
    the_number_of_matches = 0
    for j in the_title:
        if int(i[j]) == the_max_count[j]:
            the_number_of_matches += 1
        if the_number_of_matches == len(the_max_count):
            name = i["name"]

print(name)

# print("The title: ", the_title)
# print("The datebase: ", the_database)
# print("The sequence: ", the_sequence)
# print("The max count: ", the_max_count)
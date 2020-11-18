text = input("Text: ")

char_count = 0
word_count = 0
sentence_counter = 0

for i in text:
    if i.isalpha():
        char_count += 1
    elif i == " ":
        word_count += 1
    elif i in ["!", "?", "."]:
        sentence_counter += 1

word_count += 1

L = (char_count / word_count) * 100
S = (sentence_counter / word_count) * 100

grade = 0.0588 * L - 0.296 * S - 15.8
grade = round(grade)

if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print("Grade " + str(grade))
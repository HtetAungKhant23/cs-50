text = input("Text: ")

letters = 0

for c in text:
    if c.isalpha():
        letters += 1

words = len(text.split())

sentences = text.count(".") + text.count("!") + text.count("?")

l = letters / words * 100

s = sentences / words * 100

grade = 0.0588 * l - 0.296 * s - 15.8

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(grade)}")

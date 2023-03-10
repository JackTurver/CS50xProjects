# TODO

from cs50 import get_string

text = get_string("Text: ")

# letter count we will count the alphabetic characters
lettercount = 0
# word count we will count the spaces between words but start the count at 1 as the first word won't have a space
wordcount = 1
# sentence count will count the specific characters ., !, ?
sentencecount = text.count(".") + text.count("!") + text.count("?")

for character in text:
    if character.isalpha():
        lettercount += 1
    elif character.isspace():
        wordcount += 1

L = lettercount / wordcount * 100
S = sentencecount / wordcount * 100

ColemanIndex = 0.0588 * L - 0.296 * S - 15.8
# need to not truncate the value of the Coleman index but then round to nearest integer
grade = round(ColemanIndex, 0)

if grade > 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade %2d" % grade)


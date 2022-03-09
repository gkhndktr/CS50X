from cs50 import get_string

text = get_string("what is your string?: ")
letter = 0
words = 1 
# word quantity increases with space. It starts with " 1" for the first word
sentence = 0

for check in text:
    # this loop will count every letters, words and sentences
    if check.isalpha():
        letter +=1
    if check == " ":
        words +=1
    if check == '.' or check == '!' or check == '?':
        sentence +=1
        
L = (letter * 100) / words 
# L is the average number of letters per 100 words in the text
S = (sentence * 100) / words
# S is the average number of sentences per 100 words in the text.

index = round(0.0588 * L - 0.296 * S - 15.8)
# //this formula is given before

if index > 16:
    print("Grade 16+")
if index < 1:
    print("Before Grade 1")
if index > 1 and index <= 16:
    print(f"Grade {index}")

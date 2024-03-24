import re
import math


def main():
    text = input("Text: ")

    words = len(text.split())
    letters = sum(c.isalpha() for c in text)
    sentences = len(re.split(r'[.!?]\s+', text))

    L = 100.0 * (letters / words)
    S = 100.0 * (sentences / words)

    index = 0.0588 * L - 0.296 * S - 15.8
    
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


main()

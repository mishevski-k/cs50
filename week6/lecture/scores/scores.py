# scores = [72, 73, 33]

# average = sum(scores) / len(scores)

# print(f"Average: {average:.3f}")

from cs50 import get_int

scores = []
for i in range(3):
    score = get_int("Scores: ")
    scores.append(score)

average = sum(scores) / len(scores)

print(f"Average: {average:.3f}")
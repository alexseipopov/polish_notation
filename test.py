from random import choice
arr = ["(", ")", "+", "-", "*", "^", "/", "mod", "sin", "cos", "tan", "NUM", "NUM", "NUM", "NUM", "NUM"]

# for _ in range(10):
res = " ".join(choice(arr) for _ in range(10))
print(res)
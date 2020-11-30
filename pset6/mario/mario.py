# import get_int function
from cs50 import get_int

# set height as 0
height = 0

# Prompt int
while not (height >= 1 and height <= 8):
    height = get_int("Height: ")

# Draw pyramid


def pyramid(h):
    tmp = height
    if h == 0:
        return
    else:
        pyramid(h-1)
        for i in range(tmp - h):
            print(" ", end="")
        for i in range(h):
            print("#", end="")
        print()


# Print pyramid
pyramid(height)
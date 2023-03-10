# TODO

from cs50 import get_int

# need to initialise height so it can be used in the while loop to force an 0 < int < 8
height = -1
while (height > 8 or height <= 0):
    height = get_int("Height: ")

# initialise the varibales that change each new row
m = height - 1
n = 1

# loop over each row and print the pattern accordingly
for i in range(height):
    if n == height:
        m = 0
    print(" " * m, "#" * n, "  ", "#" * n, sep="")
    n += 1
    m -= 1
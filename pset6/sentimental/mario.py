from cs50 import get_int


def left_triangle(h, i):
    for j in range(1, h + 1):
        if (j < i):
            print(' ', end='')
        else:
            print("#", end='')


def right_triangle(h, i):
    for j in range(1, h + 1):
        if (j <= i):
            print("#", end='')


def get_positive_int(prompt):
    """Prompt user for positive integer"""
    while True:
        n = get_int(prompt)
        if 0 <= n and n < 24:
            break
    return n


h = get_positive_int("Height: ")

for i in range(h, 0, -1):
    left_triangle(h, i)
    print('  ', end='')
    right_triangle(h, h - i + 1)
    print("")
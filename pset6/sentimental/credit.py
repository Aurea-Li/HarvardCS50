#
# Determines if a credit card is valid, and if it is,
# returns provider.
#

from cs50 import get_string

# Function to take credit card number from user
def string(prompt):
    n = get_string(prompt)
    return n


sum_even = 0
sum_odd = 0

credit = string("Credit : ")

# Check if valid number of digits
length = len(credit)

# check credit card correct length
if (length == 16 or length == 15 or length == 13):
    for i in range(0,length):

        # even digit
        if ((i + 1) % 2 == 0):
            prod = int(credit[length - i - 1]) * 2

            # add prod digits together
            sum = 0
            for pc in str(prod):
                sum = sum + int(pc)

            sum_even = sum_even + sum

        # odd digit
        else:
            sum_odd = sum_odd + int(credit[length - i - 1])

    # Determine provider
    first = int(credit[0])
    second = int(credit[1])
    total = sum_odd + sum_even

    # check that sum ends in 0, a sign of a valid credit card number
    if (total % 10 == 0):
        if (length == 15 and first == 3):
            print("AMEX")
        elif (length == 13 and first == 4):
            print("VISA")
        elif (length == 16 and first == 4):
            print("VISA")
        elif (length == 16 and first == 5 and (second >= 1 and second <= 5)):
            print("MASTERCARD")
    else:
        print("INVALID")

else:
    print("INVALID")
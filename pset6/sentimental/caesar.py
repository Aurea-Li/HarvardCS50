#
# Returns scrambled message using caesar's algorithm
#

import sys
from cs50 import get_string

def get_(prompt):
    """Prompt user for positive integer"""
    while True:
        n = get_int(prompt)
        if 0 <= n and n < 24:
            break
    return n

def main():


    # error checking
    if len(sys.argv) != 2:
        print("Liar liar pants on fire!")
        sys.exit(1)


    else:
        plaintext = get_string("plaintext: ")
        key = int(sys.argv[1])
        ciphertext = ''

        for c in plaintext:

            # lowercase
            if (ord('a') <= ord(c) and ord(c) <= ord('z')):
                ciphertext = ciphertext + chr(((ord(c) - 96 + key) % 26) + 96)

            # uppercase
            elif (ord('A') <= ord(c) and ord(c) <= ord('Z')):
                ciphertext = ciphertext + chr(((ord(c) - 64 + key) % 26) + 64)

            else:
                ciphertext = ciphertext + c

        print(f"ciphertext: {ciphertext}")
        sys.exit(0)



if __name__ == "__main__":
    main()


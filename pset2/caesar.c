#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Error checking
    if (argc != 2)
    {
        printf("Liar liar pants on fire!\n");
        return 1;
    }
    else
    {

        printf("plaintext: ");
        string plaintext = get_string();
        char ciphertext[strlen(plaintext)];

        int key = atoi(argv[1]);

        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            if ('a' <= plaintext[i] && plaintext[i] <= 'z')
            {
                ciphertext[i] = (((int) plaintext[i] - 96 + key) % 26) + 96;
            }
            else if ('A' <= plaintext[i] && plaintext[i] <= 'Z')
            {
                ciphertext[i] = (char) (((int) plaintext[i] - 64 + key) % 26) + 64;
            }
            // If special character, save as is
            else
            {
                ciphertext[i] = plaintext[i];
            }
        }
        printf("ciphertext: %s\n",ciphertext);
        return 0;
    }
}
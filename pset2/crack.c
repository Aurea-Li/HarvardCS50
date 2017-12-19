#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <crypt.h>
#define _XOPEN_SOURCE
#include <unistd.h>

void brutecrack(char cap1, char cap2, char cap3, char cap4, char ASCII[], string masterhash);

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

        char ASCII[52];
        string masterhash = argv[1];

        // Initializing ASCII array
        for (int i = 65; i <= 90; i++)
        {
            ASCII[i-65] = (char) i;
        }

        for (int i = 97; i <= 122; i++)
        {
            ASCII[i-71] = (char) i;
        }

        // Iterates over all possible 4 letter alphabetic combinations based on user inputs for capital/lowercase letters

        char salt[] = "50";
        char *hashed;
        char pass[4];


        // Brute force password guessing
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j <= 52; j++)
            {
                for (int k = 0; k <= 52; k++)
                {
                    for (int l = 0; l <= 52; l++)
                    {
                        pass[0] = ASCII[i];
                        pass[1] = ASCII[j];
                        pass[2] = ASCII[k];
                        pass[3] = ASCII[l];

                        // Hashing guessed password
                        hashed = crypt(pass,salt);

                        if (strcmp(hashed,masterhash) == 0)
                        {
                            printf("%s\n",pass);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}








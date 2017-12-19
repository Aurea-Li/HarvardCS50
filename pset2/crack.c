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

        brutecrack('l','l','l','l', ASCII, masterhash);

        //brutecrack('u','l','l','l', ASCII, masterhash);
        //brutecrack('u','u','u','u', ASCII, masterhash);



    }

}


// Iterates over all possible 4 letter alphabetic combinations based on user inputs for capital/lowercase letters
void brutecrack(char cap1, char cap2, char cap3, char cap4, char ASCII[], string masterhash)
{
    int cap1_min, cap1_max, cap2_min, cap2_max, cap3_min, cap3_max, cap4_min, cap4_max;
    char salt[] = "50";
    char *hashed;
    char pass[4];

    // Determining min amd max iterations based on whether user wants to try capital or lowercase letters
    if (cap1 == 'l')
    {
       cap1_min = 26;
       cap1_max = 51;

    }
    else if (cap1 == 'u')
    {
        cap1_min = 0;
        cap1_max = 26;
    }
    else
    {
        printf("Error: wrong inputs!");
        return;
    }

    if (cap2 == 'l')
    {
       cap2_min = 26;
       cap2_max = 51;

    }
    else if (cap2 == 'u')
    {
        cap2_min = 0;
        cap2_max = 26;
    }
    else
    {
        printf("Error: wrong inputs!");
        return;
    }

    if (cap3 == 'l')
    {
       cap3_min = 26;
       cap3_max = 51;

    }
    else if (cap3 == 'u')
    {
        cap3_min = 0;
        cap3_max = 26;
    }
    else
    {
        printf("Error: wrong inputs!");
        return;
    }

    if (cap4 == 'l')
    {
       cap4_min = 26;
       cap4_max = 51;

    }
    else if (cap4 == 'u')
    {
        cap4_min = 0;
        cap4_max = 26;
    }
    else
    {
        printf("Error: wrong inputs!");
        return;
    }

    // Brute force password guessing
    for (int i = cap1_min; i <= cap1_max; i++)
    {
        for (int j = cap2_min; j <= cap2_max; j++)
        {
            for (int k = cap3_min; k <= cap3_max; k++)
            {
                for (int l = cap4_min; l <= cap4_max; l++)
                {
                    pass[0] = ASCII[i];
                    pass[1] = ASCII[j];
                    pass[2] = ASCII[k];
                    pass[3] = ASCII[l];

                    // Hashing guessed password
                    hashed = crypt(pass,salt);

                     if (memcmp(pass, "andi", sizeof(pass)) == 0)
                     {
                         printf("AAA Password: %s , ", pass);
                         printf("AAA Hashed: %s\n",hashed);
                     }

                    if (strcmp(hashed,masterhash) == 0)
                    {
                        printf("SOLVED! Password is %s\n",pass);
                        return;
                    }

                }
            }
        }
    }
}
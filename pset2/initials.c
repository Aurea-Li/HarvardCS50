#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argv != NULL)
    {
        for (int i = 1; i < argc; i++)
        {
            // Print first letter (capitalized) of each string
            printf("%c", toupper(argv[i][0]));


        }
        printf("\n");
        return 0;
    }
    else
    {
        return 1;
    }
}
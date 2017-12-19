#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isletter(char c);

int main(void)
{

    string name = get_string();

    if (name != NULL)
    {
        if (name[0] != ' ')
        {
            printf("%c", toupper(name[0]));
        }

        for (int i = 1, n = strlen(name); i < n; i++)
        {
            // Print first letter (capitalized) of each string
            if (isletter(name[i]) == 0 && name[i-1] == ' ')
            {
                printf("%c", toupper(name[i]));
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Error: No input given.\n");
        return 1;
    }

}

// function that returns 0 if is ASCII character, 1 otherwise
int isletter(char c)
{
    if (65 <= c && c <= 122)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
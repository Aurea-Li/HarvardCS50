#include <stdio.h>
#include <cs50.h>

void mario(void);
void left_triangle(int h, int i);
void right_triangle(int h, int i);

int main(void)
{

    mario();
}

void mario(void)
{
    int h = -1;

    while (h < 0 || h > 23)
    {
        printf("Height: ");
        h = get_int();
    }

    for (int i = h; i >= 1; i--)
    {

        left_triangle(h, i);
        printf("  ");
        right_triangle(h, h - i + 1);
        printf("\n");

    }


}

void left_triangle(int h, int i)
{
    for (int j = 1; j <= h; j++)
    {
        if (j < i)
        {
            printf(" ");
        }
        else
        {
            printf("#");
        }
    }
}

void right_triangle(int h, int i)
{
    for (int j = 1; j <= h; j++)
    {
        if (j <= i)
        {
            printf("#");
        }
        else
        {
            printf(" ");
        }
    }
}
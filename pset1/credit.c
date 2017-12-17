#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Prototypes
int length(long long num);
int digit(long long num, int n);

int main(void)
{
    long long credit;
    int sum_even = 0;
    int sum_odd = 0;

    printf("Credit : ");
    credit = get_long_long();


    // Check if vaild number of digits
    if (length(credit) == 16 || length(credit) == 15 || length(credit) == 13)
    {
        for (int i = 1; i <= length(credit); i++)
        {
            // Even digits
            if (i % 2 == 0)
            {

                int prod = digit(credit,i)*2;
                if (length(prod) > 1)
                {
                    int sum = 0;
                    for (int j = 1; j <= length(prod);j++)
                    {

                        sum += digit(prod,j);
                    }
                    sum_even += sum;
                }
                else
                {
                    sum_even += prod;
                }
            }
            // Odd digits
            else
            {

                sum_odd += digit(credit,i);
            }
        }

        int final_sum = sum_odd + sum_even;
        int flag = digit(final_sum,1);
        if (flag == 0)
        {
            if (length(credit) == 15)
            {
                printf("AMEX\n");
            }
            else if (length(credit) == 13)
            {
                printf("VISA\n");
            }
            else if (length(credit) == 16)
            {
                printf("VISA or MASTERCARD\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // If not valid length for credit number, automatically return INVALID
    else
    {
        printf("INVALID\n");
    }
}

/* Determines number of digits in an integer */
int length(long long num)
{
    int digits = 0;
    long long i = 10;

    while (num > 0)
    {
        num = num - (num % i);
        digits += 1;
        i *= 10;

    }

    return digits;
}

/* Returns the nth digit from integer */
int digit(long long num, int n)
{

    if (n > length(num))
    {
        int digit = -1;
        printf("Digit invalid.\n");
        return digit;
    }
    else
    {
        long long mod_n = 1;
        for (int j = 0; j < n; j++)
        {
            mod_n *= 10;
        }

        int digit = num % mod_n / (mod_n / 10);
        return digit;
    }

}
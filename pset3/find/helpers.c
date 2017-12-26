/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"


// temp header, delete after testing
#include <stdio.h>
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (value < 0)
    {
        return false;
    }
    else
    {
        // binary search
        int start = 0;
        int end = n;
        int half = end / 2;

        // if value is less than smallest item in array, or greater than greatest item in array, automatically return false
        if (value < values[0] || value > values[n-1])
        {
            return false;
        }
        // iterates until value is found or is determined to not exist
        while (values[half] != value)
        {
            // if value at midpoint is greater, search left side
            if (values[half] > value)
            {
                end = half;

            }
            // if value at midpoint is smaller, search right side
            else if (values[half] < value)
            {
                start = half;
            }
            half = (start + end) / 2;

            // check if we are where the value SHOULD be, in which case it doesn't exist
            if (values[half] < value && values[half+1] > value)
            {
                return false;
            }
        }

        return true;
    }
}

/**
 * Sorts array of n values using counting sort
 */
void sort(int values[], int n)
{
    // create counting array of size 65,536 ; set all values to zero O(c)
    int count[65536] = {0};

    // set values in counting array O(n)
    for (int i = 0; i < n; i++)
    {
        count[values[i]]++;
    }

    // copy sorted values in counting array back into original array O(c)
    int pos = 0;
    for (int j = 0; j < 65536; j++)
    {
        while (count[j] > 0)
        {
            values[pos] = j;
            pos++;
            count[j]--;
        }
    }
    return;
}

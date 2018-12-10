/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

// Повертає true, якщо значення в масиві з n значень, інше - false.
bool search(int value, int values[], int n)
{
    if (value <= 0)
        return false;
    else
    {
        if (value == values[0] || value == values[n/2] || value == values[n])
            return true;
        else if (n/2 > 0 && value < values[n/2])
            return search(value, values, n/2 - 1);
        else if (n/2 > 0 && value > values[n/2])
        {
            for (int i = 0; i <= n/2; i++)
                values[i] = values[n/2 + i];
            return search(value, values, n - n/2);
        }
        else if (n/2 == 0)
            return false;
    }
    return false;
}

// Сортує масив з n значень.
void sort(int values[], int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++)
            if (values[j] > values[j + 1])
            {
                temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
}
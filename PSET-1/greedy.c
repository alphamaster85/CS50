#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    printf("O hai!");
    do
    {
        printf("How much change is owed? ");
        dollars = get_float();
    }
    while (dollars <= 0);

    int cents = roundf(dollars * 100);
    int counter = 0;
    if (cents % 25 == 0)
    {
        counter = cents / 25;
    }
    else if ((cents % 25) % 10 == 0)
    {
        counter = cents / 25 + (cents % 25) / 10;
    }
    else if (((cents % 25) % 10) % 5 == 0)
    {
        counter = cents / 25 + (cents % 25) / 10 + ((cents % 25) % 10) / 5;
    }
    else
    {
        counter = cents / 25 + (cents % 25) / 10 + ((cents % 25) % 10) / 5 + ((cents % 25) % 10) % 5;
    }

    printf("Number of all coins: %d\n", counter);
}
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        printf("Enter the height of the pyramid: ");
        height = get_int();
    }
    while ((height > 23) || (height < 0));

    for (int i = 0; i < height; i++)
    {
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }
        for (int j = i + 1; j >= 0; j--)
        {
            printf("#");
        }
        printf("\n");
    }
}
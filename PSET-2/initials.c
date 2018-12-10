#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string fullName = NULL;
    do
    {
        printf("Enter your own name: ");
        fullName = get_string();
    }
    while (fullName == NULL);

    if (fullName[0] != ' ')
        printf("%c", toupper(fullName[0]));

    for (int i = 0, n = strlen(fullName); i < n; i++)
        if (fullName[i] != ' ')
            if (fullName[i - 1] == ' ')
                printf("%c", toupper(fullName[i]));
    printf("\n");
}
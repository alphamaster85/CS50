#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]);
        if (key <= 0)
        {
            printf("Usage key - positive number\n");
            return 2;
        }
        else
        {
            printf("Type the text you want to encrypt: ");
            string plainText;
            plainText = get_string();
            string encodedText = plainText;

            for (int i = 0, n = strlen(plainText); i < n; i++)
                if (isalpha(plainText[i]))
                    if (isupper(plainText[i]))
                        encodedText[i] = (plainText[i] - 65 + key) % 26 + 65;
                    else
                        encodedText[i] = (plainText[i] - 97 + key) % 26 + 97;
                else
                    encodedText[i] = plainText[i];

            printf("ciphertext: %s\n", encodedText);
            return 0;
        }
    }
}
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar keyword\n");
        return 1;
    }
    else
    {
        string keyword = argv[1];
        int j = 0, n1 = strlen(keyword);
        for (j = 0; j < n1; j++)
        if (!isalpha(keyword[j]))
        {
            printf("Usage in keyword - only letters\n");
            return 1;
        }
        else
        {
            if (isupper(keyword[j]))
                keyword[j] = keyword[j] - 65;
            else
                keyword[j] = keyword[j] - 97;
        }

        printf("Type the text you want to encrypt: ");
        string plainText;
        plainText = get_string();
        string encodedText = plainText;

        j = 0;
        for (int i = 0, n2 = strlen(plainText); i < n2; i++)
        {
            if (isalpha(plainText[i]))
            {
                if (isupper(plainText[i]))
                {
                    encodedText[i] = (plainText[i] - 65 + keyword[j]) % 26 + 65;
                    if (++j == n1)
                        j = 0;
                }
                else
                {
                    encodedText[i] = (plainText[i] - 97 + keyword[j]) % 26 + 97;
                    if (++j == n1)
                        j = 0;
                }
            }
            else
                encodedText[i] = plainText[i];
        }

        printf("ciphertext: %s\n", encodedText);
        return 0;
    }
}
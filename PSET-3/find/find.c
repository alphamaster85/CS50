/**
 * find.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Prompts user for as many as MAX values until EOF is reached,
 * then proceeds to search that "haystack" of values for given needle.
 * Ввід користувачем багатьох значень до досягнення EOF,
 * Потім продовжує пошук в тому "стозі сіна" значень для даної голки.
 *
 * Usage: ./find needle
 *
 * де голка - це значення для пошуку в стозі сіна
 */

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// максимальна кількість сіна
const int MAX = 65536;

int main(int argc, string argv[])
{
    // перевірка на правильність вводу
    if (argc != 2)
    {
        printf("Usage: ./find needle\n");
        return -1;
    }

    // запам'ятовує голку
    int needle = atoi(argv[1]);

    // наповняємо стог сіна
    int size;
    int haystack[MAX];
    for (size = 0; size < MAX; size++)
    {
        // чекаємо на сіно до EOF
        printf("\nhaystack[%d] = ", size);
        int straw = get_int();
        if (straw == INT_MAX)
        {
            break;
        }

        // додаємо сіно в стіг (стек)
        haystack[size] = straw;
    }
    printf("\n");

    // сортуємо
    sort(haystack, size);

    // шукаємо голку в стозі сіна
    if (search(needle, haystack, size))
    {
        printf("\nFound needle in haystack!\n\n");
        return 0;
    }
    else
    {
        printf("\nDidn't find needle in haystack.\n\n");
        return 1;
    }
}

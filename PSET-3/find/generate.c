/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Генерує псевдовипадкові числа в [0, LIMIT], по одному на рядок.
 *
 * Usage: generate n [s]
 *
 * де n - це число псевдовипадкових чисел для друку та s є додатковим насінням
 ***************************************************************************/

// стандартні бібліотеки
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// константа
#define LIMIT 65536

int main(int argc, string argv[])
{
    // перевіряємо чи введені параметри n та/або s
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // оцифровуємо перший аргумент n = argv[1]
    int n = atoi(argv[1]);

    // якщо введено параметр s - запускаємо srand48()
    // інакше srand48() повертає NULL
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // TODO: виводимо по одному в рядок числа, що згенеровані drand48()
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success - успішно
    return 0;
}

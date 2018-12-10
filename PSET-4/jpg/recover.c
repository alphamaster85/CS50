/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Відновлює JPEG із судово-медичного зображення.
 */

#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    // забезпечуємо правильний виклик RECOVER.C
    if (argc != 1)
    {
        printf("Usage: ./recover\n");
        return 2;
    }

    // записуємо ім'я файлу CARD.RAW
    char* infile = "card.raw";

    // відкриваємо вхідний файл
    FILE* INptr = fopen(infile, "r");
    if (INptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // створюємо константу з розміром BUFFER
    const int BUFFER_SIZE = 512;

    // створюємо масив BUFFER розміром BUFFER_SIZE
    unsigned char buffer[BUFFER_SIZE];

    // створюємо лічильник створених JPEG-файлів
    int file_counter = 0;

    // створюємо масив символів назви JPEG-файлу
    char outfile[8];

    // створюємо вказівник на вихідний файл
    FILE* OUTptr = NULL;

    // читаємо 512 byte з CARD.RAW і записуємо у вказівник BUFFER шлях до нього
    while (fread(&buffer, BUFFER_SIZE, 1, INptr))
    {
        // перевірємо чи перші чотири байти є підписом JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // перевірємо чи створений вихідний файл
            if (OUTptr != NULL)
            {
                // закриваємо вихідний файл
                fclose(OUTptr);
            }

            // записуємо в OUTFILE назву наступного JPEG-файлу
            sprintf(outfile, "%03d.jpg", file_counter);

            // збільшуємо лічильник
            file_counter++;

            // відкриваємо вихідний файл
            OUTptr = fopen(outfile, "w");
        }

        // перевірємо чи створений вихідний файл
        if (OUTptr != NULL)
        {
            // записуємо BUFFER у вихідний файл
            fwrite(buffer, BUFFER_SIZE, 1, OUTptr);
        }
    }

    // перевірємо чи створений вихідний файл
    if (OUTptr != NULL)
    {
        // закриваємо вихідний файл
        fclose(OUTptr);
    }

    // закриваємо вхідний файл
    fclose(INptr);

    // це все, шановні
    return 0;
}

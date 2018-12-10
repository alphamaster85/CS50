/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Копіює частину BMP за штукою, просто тому.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // забезпечити правильний виклик WHODUNIT.C
    if (argc != 4)
    {
        printf("Usage: ./resize n INFILE OUTFILE\n");
        return 1;
    }

    // записуємо коефіцієнт збільшення фалу
    int multiplicity = atoi(argv[1]);
    if (multiplicity <= 0 || multiplicity > 100)
    {
        printf("Error: n must be beetwen 1 and 100\n");
        return 2;
    }

    // записуємо імена файлів INFILE та OUTFILE
    char* infile = argv[2];
    char* outfile = argv[3];

    // відкриваємо вхідний файл
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // відкриваємо вихідний файл
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // читаємо BITMAPFILEHEADER з INFILE і записуємо у вказівник BF шлях до нього
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // читаємо BITMAPINFOHEADER з INFILE і записуємо у вказівник BI шлях до нього
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // перевіряємо, що INFILE є 24-розрядний нескомпресований BMP
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // зберігамо оригінальні кількості пікселів по ширині і висоті та заповнення
    int biWidth_original = bi.biWidth;
    int biHeight_original = abs(bi.biHeight);
    int padding_original =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // записуємо новий розмір файла в BITMAPFILEHEADER і BITMAPINFOHEADER
    printf("bf.bfSize = %d, bi.biSizeImage = %d, biWidth = %d, biHeight = %d, padding = %d\n", bf.bfSize, bi.biSizeImage, bi.biWidth, bi.biHeight, padding_original);

    bi.biWidth = multiplicity * bi.biWidth;
    bi.biHeight = multiplicity * bi.biHeight;
    if ((bi.biWidth * sizeof(RGBTRIPLE)) % 4 == 0)
    {
        bi.biSizeImage = bi.biWidth * 3 * abs(bi.biHeight);
        bf.bfSize = 54 + bi.biSizeImage;
    } else
    {
        bi.biSizeImage = (bi.biWidth * 3 + (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4) * abs(bi.biHeight);
        bf.bfSize = 54 + bi.biSizeImage;
    }

    // записуємо BITMAPFILEHEADER в OUTFILE
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // записуємо BITMAPINFOHEADER в OUTFILE
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // визначаємо кількість пікселів заповнення
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("bf.bfSize = %d, bi.biSizeImage = %d, biWidth = %d, biHeight = %d, padding = %d\n\n", bf.bfSize, bi.biSizeImage, bi.biWidth, bi.biHeight, padding);

    // ітерація по рядках INFILE
    for (int i = 0; i < biHeight_original; i++)
    {
        // створюємо тимчасовий масив TEMP для зберігання рядка пікселів і лічильник
        RGBTRIPLE temp[bi.biWidth];
        int r = 0;

        // ітерація по пікселях в рядку INFILE
        for (int j = 0; j < biWidth_original; j++)
        {
            // створюємо тимчасовий TRIPLE для зберігання пікселя
            RGBTRIPLE triple;

            // читаємо RGBTRIPLE з INFILE
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // ітерація по пікселях збільшених на коефіцієнт MULTIPLICITY
            for (int l = 1; l <= multiplicity; l++)
            {
                //записуємо RGBTRIPLE в OUTFILE
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                // записуємо TRIPLE в TEMP + збільшуємо лічильник
                temp[r++] = triple;
            }
        }

        // пропускаємо повзунок, якщо є пікселі заповнення
        fseek(inptr, padding_original, SEEK_CUR);

        // записуємо в OUTFILE нульові пікселі
        for (int p = 0; p < padding; p++)
        {
            fputc(0x00, outptr);
        }

        // ітерація по рядках збільшених на коефіцієнт MULTIPLICITY
        for (int k = 1; k < multiplicity; k++)
        {
            // ітерація по масиву TEMP
            for (int s = 0; s < r; s++)
            {
                // записуємо TEMP в OUTFILE
                fwrite(&temp[s], sizeof(RGBTRIPLE), 1, outptr);
            }

            // дозаписуємо в OUTFILE нульові пікселі
            for (int p = 0; p < padding; p++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // закриваємо INFILE
    fclose(inptr);

    // закриваємо OUTFILE
    fclose(outptr);

    // це все, шановні
    return 0;
}

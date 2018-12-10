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

#include "bmp.h"

int main(int argc, char* argv[])
{
    // забезпечити правильне використання
    if (argc != 3)
    {
        printf("Usage: ./copy INFILE OUTFILE\n");
        return 1;
    }

    // запам'ятати імена файлів
    char* infile = argv[1];
    char* outfile = argv[2];

    // відкрити вхідний файл
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // відкрити вихідний файл
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // читайте BITMAPFILEHEADER infile
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // читати infital's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Переконайтеся, що infile є (імовірно) 24-розрядний нескомпресований BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // написати BITMAPFILEHEADER outfile
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // написати BITMAPINFOHEADER outfile
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // визначити заповнення для сканування ліній
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // ітерація над сканеліями infile
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // ітерація по пікселях по scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // тимчасовий зберігання
            RGBTRIPLE triple;

            // читати RGB потрійний від infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // запис RGB потрійний для outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // пропустити повзунок, якщо такі є
        fseek(inptr, padding, SEEK_CUR);

        // потім додати його назад (щоб продемонструвати, як)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // закрити infile
    fclose(inptr);

    // закрити outfile
    fclose(outptr);

    // це все, шановні
    return 0;
}

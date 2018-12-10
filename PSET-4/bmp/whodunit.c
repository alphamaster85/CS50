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
    // забезпечити правильний виклик WHODUNIT.C
    if (argc != 3)
    {
        printf("Usage: ./copy INFILE OUTFILE\n");
        return 1;
    }

    // запам'ятати імена файлів INFILE та OUTFILE
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

    // читаємо BITMAPFILEHEADER з INFILE і записуємо у вказівник BF шлях до нього
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // читаємо BITMAPINFOHEADER з INFILE і записуємо у вказівник BI шлях до нього
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Перевіряємо, що INFILE є 24-розрядний нескомпресований BMP
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // записуємо BITMAPFILEHEADER в OUTFILE
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // записуємо BITMAPINFOHEADER в OUTFILE
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // визначаємо кількість пікселів заповнення
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // ітерація по рядках INFILE
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // ітерація по пікселях в рядку INFILE
        for (int j = 0; j < bi.biWidth; j++)
        {
            // тимчасовий зберігання
            RGBTRIPLE triple;

            // читаємо RGBTRIPLE з INFILE
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // перевіряємо чи є TRIPLE 0x0000ff
            if (triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00 && triple.rgbtRed == 0xff)
            {
                // записуємо 0xffffff в OUTFILE замість RED
                fputc(0xff, outptr);
                fputc(0xff, outptr);
                fputc(0xff, outptr);
            }
            else
            {
                // записуємо RGBTRIPLE в OUTFILE
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // пропускаємо повзунок, якщо є пікселі заповнення
        fseek(inptr, padding, SEEK_CUR);

        // записуємо в OUTFILE нульові пікселі
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // закриваємо INFILE
    fclose(inptr);

    // закриваємо OUTFILE
    fclose(outptr);

    // це все, шановні
    return 0;
}

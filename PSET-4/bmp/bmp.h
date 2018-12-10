/**
 * bmp.h
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Типи даних, пов'язаних із BMP, на основі власного Microsoft.
 */

#include <stdint.h>

/**
 * Common Data Types
 *
 * Типи даних у цьому розділі є псевдонімами для примітивних типів даних C / C ++.
 *
 * Адаптовано з http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * Подивитися http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPFILEHEADER
 *
 * Структура BITMAPFILEHEADER містить інформацію про тип, розмір та макет файлу, який містить DIB [незалежний від пристрою растровий малюнок].
 *
 * Адаптовано з http://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx.
 */
typedef struct
{
    WORD   bfType;
    DWORD  bfSize;
    WORD   bfReserved1;
    WORD   bfReserved2;
    DWORD  bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

/**
 * BITMAPINFOHEADER
 *
 * Структура BITMAPINFOHEADER містить інформацію про розміри та формат кольорів DIB [незалежний від пристрою растровий малюнок].
 *
 * Адаптовано з http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx.
 */
typedef struct
{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

/**
 * RGBTRIPLE
 *
 * Ця структура описує колір, що складається з відносної інтенсивності червоного, зеленого та синього кольорів.
 *
 * Адаптовано з http://msdn.microsoft.com/en-us/library/aa922590.aspx.
 */
typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;

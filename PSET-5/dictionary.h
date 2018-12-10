/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Повертає TRUE, якщо слово в словнику, інакше - FALSE.
bool check(const char* word);

// Завантажує словник у пам'ять. Повертає TRUE, якщо успішно, інакше - FALSE.
bool load(const char* dictionary);

// Повертає кількість слів у словнику, що завантажений і - 0, якщо він ще не завантажений.
unsigned int size(void);

// Вивантажує словник із пам'яті. Повертає TRUE, інакше - FALSE.
bool unload(void);

#endif // DICTIONARY_H

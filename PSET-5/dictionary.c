/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"

// встановлюємо розмір HASH-таблиці
#define SIZE 1000000

// створюємо вузли для зв'язаного списку
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

// створюємо HASH-таблицю
node* hashtable[SIZE] = {NULL};

// створюємо HASH-функцію
int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // якщо літери
        if(isalpha(word[i]))
            n = word[i] - 'a' + 1;

        // якщо апостроф
        else
            n = 27;

        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;
}

// створюємо глобальну змінну для підрахунку розміру словника
int dictionarySize = 0;

// Повертає TRUE, якщо слово в словнику, інакше - FALSE.
bool check(const char* word)
{
    // створюємо TEMP-змінну, яка зберігає версію слова у нижньому регістрі
    char temp[LENGTH + 1];
    int end = strlen(word);
    for(int i = 0; i < end; i++)
        temp[i] = tolower(word[i]);
    temp[end] = '\0';

    // шукаємо який індекс масиву має бути таким словом
    int index = hash(temp);

    // повертаємо FALSE якщо HASH-таблиця в цьому індексі порожня
    if (hashtable[index] == NULL)
        return false;

    // створюємо курсор для порівняння зі словом
    node* cursor = hashtable[index];

    // перебираємо масив і порівнюємо якщо HASH-таблиця в цьому індексі НЕ порожня
    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->word) == 0)
            return true;
        cursor = cursor->next;
    }

    // повертаємо FALSE якщо НЕ знайшли слова
    return false;
}

// Завантажує словник у пам'ять. Повертає TRUE, якщо успішно, інакше - FALSE.
bool load(const char* dictionary)
{
    // відкриваємо словник
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
        return false;

    // створюємо масив для слова, яке буде збережено
    char word[LENGTH+1];

    // скануємо файл, завантажумо кожне слово в HASH-таблицю
    while (fscanf(file, "%s\n", word)!= EOF)
    {
        // збільшуємо глобальну змінну для підрахунку розміру словника
        dictionarySize++;

        // виділяємо пам'ять для нового слова
        node* newWord = malloc(sizeof(node));

        // вводимо слово в новий вузол
        strcpy(newWord->word, word);

        // знаходимо, який індекс масиву має входити слово
        int index = hash(word);

        // вставляємо, якщо HASH-таблиця порожня на цьому індексі
        if (hashtable[index] == NULL)
        {
            hashtable[index] = newWord;
            newWord->next = NULL;
        }

        //  вставляємо, якщо HASH-таблиця НЕ порожня на цьому індексі
        else
        {
            newWord->next = hashtable[index];
            hashtable[index] = newWord;
        }
    }

    // закриваємо файл
    fclose(file);

    // повертаємо TRUE якщо все успішно
    return true;
}

// Повертає кількість слів у словнику, що завантажений і - 0, якщо він ще не завантажений.
unsigned int size(void)
{
    // повертаємо кількість слів, якщо словник завантажений
    if (dictionarySize != 0)
        return dictionarySize;

    // повертаємо 0, якщо словник НЕ завантажений
    else
        return 0;
}

// Вивантажує словник із пам'яті. Повертає TRUE, інакше - FALSE.
bool unload(void)
{
    // створємо змінну для індекса
    int index = 0;

    // ітеруємо HASH-таблицю
    while (index < SIZE)
    {
        // переходимо до наступного індексу, якщо HASH-таблиця порожня в цьому
        if (hashtable[index] == NULL)
            index++;

        // ітеруємо вузли і очищаємо їх, якщо HASH-таблиця НЕ порожня в цьому
        else
        {
            while(hashtable[index] != NULL)
            {
                node* cursor = hashtable[index];
                hashtable[index] = cursor->next;
                free(cursor);
            }

            // збільшуємо індекс
            index++;
        }
    }

    // повертаємо TRUE якщо все успішно
    return true;
}

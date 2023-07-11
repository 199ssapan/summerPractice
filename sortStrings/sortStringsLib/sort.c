#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

int myStrlen(char* string)
{
    int i;
    for (i = 0; string[i] != '\0'; i++){};
    return i;
}

FILE* getFileWRandStrings(char* filePath)
{
    int p = time(0);
    srand((int)&p ^ p);
    FILE* file = fopen(filePath, "w");
    unsigned count = rand() % MAX_STRINGS_COUNT + 30;
    unsigned maxLen = rand() % (MAX_STRING_SIZE * 2) + 35;
    char** strings = generateStrings(count, maxLen);
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", strings[i]);
    }
    fclose(file);
    return file;
}

char* generateString(unsigned maxSize)
{
    int size = rand() % (maxSize) + 1;
    char* alphabet = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    int alphaLen = myStrlen(alphabet);
    char* string = (char*)malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < size; i++)
    {
        string[i] = alphabet[rand() % alphaLen];
    }
    string[size] = '\0';
    return string;
}

char** generateStrings(unsigned count, unsigned maxStringSize)
{
    char** strings = (char**)malloc(sizeof(char*) * count);
    for (int i = 0; i < count; i++)
    {
        strings[i] = generateString(maxStringSize);
    }
    return strings;
}

int ReadStringsToArrays(FILE* file, char staticArray[][MAX_STRING_SIZE], char*** dynamicArray)
{
    char** newDynamicArray = (char**)malloc(sizeof(char*) * MAX_STRINGS_COUNT);
    char c;
    int j;
    for (int i = 0; i < MAX_STRINGS_COUNT; i++)
    {
        j = 0;
        while ((c = fgetc(file)) != '\n' && c != EOF && j != MAX_STRING_SIZE)
        {
            staticArray[i][j] = c;
            j++;
        }
        if (c == '\n' || c == EOF)
        {
            staticArray[i][j] = '\0';
        }
        
        j = 0;

        newDynamicArray[i] = (char*)malloc(sizeof(char));
        while (c != '\n' && c != EOF)
        {
            newDynamicArray[i][j] = c;
            j++;
            c = fgetc(file);
            newDynamicArray[i] = (char*)realloc(newDynamicArray[i], sizeof(char) * (j + 1));
        }
        newDynamicArray[i][j] = '\0';
    }
    *dynamicArray = newDynamicArray;
    return 0;
}

int lenStatic(char str[MAX_STRING_SIZE])
{
    int i ;
    for (i = 0; i < MAX_STRING_SIZE && str[i] != '\0'; i++) {}
    return i;
}

int lenDynamic(char* str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++) {}
    return i;
}

int cmpByLexGraphOrderWOCaseStraight(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j)
{
    int staticLeni = lenStatic(staticArray[i]);
    int staticLenj = lenStatic(staticArray[j]);
    int dynamicLeni = lenDynamic(dynamicArray[i]);
    int dynamicLenj = lenDynamic(dynamicArray[j]);
    int minStaticLen = (staticLeni < staticLenj) ? staticLeni : staticLenj;
    int minDynamicLen = (dynamicLeni < dynamicLenj) ? dynamicLeni : dynamicLenj;
    char* lowerStatici = myToLowerStatic(staticArray[i]);
    char* lowerStaticj = myToLowerStatic(staticArray[j]);
    char* lowerDynamici = myToLowerDynamic(dynamicArray[i]);
    char* lowerDynamicj = myToLowerDynamic(dynamicArray[j]);
    for (int p = 0; p < minStaticLen; p++)
    {
        if (lowerStatici[p] > lowerStaticj[p])
        {
            return 1;
        }
        else if (lowerStatici[p] < lowerStaticj[p])
        {
            return 0;
        }
    }
    if (staticLeni > staticLenj) return 1;
    else if (staticLeni < staticLenj) return 0;
    for (int p = 0; p < minDynamicLen; p++)
    {
        if (lowerDynamici[p] > lowerDynamicj[p])
        {
            return 1;
        }
        else if (lowerDynamici[p] < lowerDynamicj[p]) return 0;
    }
    if (dynamicLeni > dynamicLenj) return 1;
    else if (dynamicLeni < dynamicLenj) return 0;
    else return 0;
}

int cmpByLexGraphOrderWOCaseReverse(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j)
{
    int staticLeni = lenStatic(staticArray[i]);
    int staticLenj = lenStatic(staticArray[j]);
    int dynamicLeni = lenDynamic(dynamicArray[i]);
    int dynamicLenj = lenDynamic(dynamicArray[j]);
    int minStaticLen = (staticLeni < staticLenj) ? staticLeni : staticLenj;
    int minDynamicLen = (dynamicLeni < dynamicLenj) ? dynamicLeni : dynamicLenj;
    char* lowerStatici = myToLowerStatic(staticArray[i]);
    char* lowerStaticj = myToLowerStatic(staticArray[j]);
    char* lowerDynamici = myToLowerDynamic(dynamicArray[i]);
    char* lowerDynamicj = myToLowerDynamic(dynamicArray[j]);
    for (int p = 0; p < minStaticLen; p++)
    {
        if (lowerStatici[p] < lowerStaticj[p])
        {
            return 1;
        }
        else if (lowerStatici[p] > lowerStaticj[p]) return 0;
    }
    if (staticLeni < staticLenj) return 1;
    else if (staticLeni > staticLenj) return 0;
    for (int p = 0; p < minDynamicLen; p++)
    {
        if (lowerDynamici[p] < lowerDynamicj[p])
        {
            return 1;
        }
        else if (lowerDynamici[p] > lowerDynamicj[p]) return 0;
    }
    if (dynamicLeni < dynamicLenj) return 1;
    else if (dynamicLeni > dynamicLenj) return 0;
    else return 0;
}

int cmpByLexGraphOrderStraight(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j)
{
    int staticLeni = lenStatic(staticArray[i]);
    int staticLenj = lenStatic(staticArray[j]);
    int dynamicLeni = lenDynamic(dynamicArray[i]);
    int dynamicLenj = lenDynamic(dynamicArray[j]);
    int minStaticLen = (staticLeni < staticLenj) ? staticLeni : staticLenj;
    int minDynamicLen = (dynamicLeni < dynamicLenj) ? dynamicLeni : dynamicLenj;

    for (int p = 0; p < minStaticLen; p++)
    {
        if (staticArray[i][p] > staticArray[j][p])
        {
            return 1;
        }
        else if (staticArray[i][p] < staticArray[j][p])
        {
            return 0;
        }
    }
    if (staticLeni > staticLenj) return 1;
    else if (staticLeni < staticLenj) return 0;
    for (int p = 0; p < minDynamicLen; p++)
    {
        if (dynamicArray[i][p] > dynamicArray[j][p])
        {
            return 1;
        }
        else if (dynamicArray[i][p] < dynamicArray[j][p]) return 0;
    }
    if (dynamicLeni > dynamicLenj) return 1;
    else if (dynamicLeni < dynamicLenj) return 0;
    else return 0;
}

int cmpByLexGraphOrderReverse(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j)
{
    int staticLeni = lenStatic(staticArray[i]);
    int staticLenj = lenStatic(staticArray[j]);
    int dynamicLeni = lenDynamic(dynamicArray[i]);
    int dynamicLenj = lenDynamic(dynamicArray[j]);
    int minStaticLen = (staticLeni < staticLenj) ? staticLeni : staticLenj;
    int minDynamicLen = (dynamicLeni < dynamicLenj) ? dynamicLeni : dynamicLenj;

    for (int p = 0; p < minStaticLen; p++)
    {
        if (staticArray[i][p] > staticArray[j][p])
        {
            return 1;
        }
        else if (staticArray[i][p] < staticArray[j][p])
        {
            return 0;
        }
    }
    if (staticLeni < staticLenj) return 1;
    else if (staticLeni > staticLenj) return 0;
    for (int p = 0; p < minDynamicLen; p++)
    {
        if (dynamicArray[i][p] > dynamicArray[j][p])
        {
            return 1;
        }
        else if (dynamicArray[i][p] < dynamicArray[j][p]) return 0;
    }
    if (dynamicLeni < dynamicLenj) return 1;
    else if (dynamicLeni > dynamicLenj) return 0;
    else return 0;
}


char* myToLowerDynamic(char* str)
{
    int len = lenDynamic(str);
    char* newStr = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z') newStr[i] = (char)(str[i] - 'A' + 'a');
        else newStr[i] = str[i];
    }
    newStr[len] = '\0';
    return newStr;
}

char* myToLowerStatic(char str[MAX_STRING_SIZE])
{
    int len = lenStatic(str);
    char* newStr = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z') newStr[i] = (char)(str[i] - 'A' + 'a');
        else newStr[i] = str[i];
    }
    newStr[len] = '\0';
    return newStr;
}

int cmpByLenStraight(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j)
{
    int staticLeni = lenStatic(staticArray[i]);
    int staticLenj = lenStatic(staticArray[j]);
    int dynamicLeni = lenDynamic(dynamicArray[i]);
    int dynamicLenj = lenDynamic(dynamicArray[j]);
    if (staticLeni + dynamicLeni > staticLenj + dynamicLenj) return 1;
    else return 0;
}

int cmpByLenReverse(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j)
{
    int staticLeni = lenStatic(staticArray[i]);
    int staticLenj = lenStatic(staticArray[j]);
    int dynamicLeni = lenDynamic(dynamicArray[i]);
    int dynamicLenj = lenDynamic(dynamicArray[j]);
    if (staticLeni + dynamicLeni < staticLenj + dynamicLenj) return 1;
    else return 0;
}

void printStrings(char staticArray[][MAX_STRING_SIZE], char** dynamicArray)
{
    int j;
    for (int i = 0; i < MAX_STRINGS_COUNT; i++)
    {
        j = 0;
        while (staticArray[i][j] != '\0' && j != MAX_STRING_SIZE)
        {
            printf("%c", staticArray[i][j]);
            j++;
        }
        printf("_");
        printf("%s\n", dynamicArray[i]);
    }
}

void SortStrings (char staticStrings[][MAX_STRING_SIZE], char **dynamicStrings, int (*compareStringsFunction)(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j))
{
    for (int i = 0; i < MAX_STRINGS_COUNT; i++)
    {
        for (int j = 0; j < MAX_STRINGS_COUNT - 1; j++)
        {
           if (compareStringsFunction(staticStrings, dynamicStrings, j, j + 1))
           {
            swapStatic(staticStrings[j], staticStrings[j + 1]);
            swapdynamic(&dynamicStrings[j], &dynamicStrings[j + 1]);
           } 
        }
    }
}

void swapdynamic(char** f, char** s)
{
    char* tmp = *f;
    *f = *s;
    *s = tmp;
}

void swapStatic(char str1[MAX_STRING_SIZE], char str2[MAX_STRING_SIZE])
{
    char buf[MAX_STRING_SIZE];
    int i = 0;
    while (str1[i] != '\0' && i != MAX_STRING_SIZE)
    {
        buf[i] = str1[i];
        i++;
    }
    if (i != MAX_STRING_SIZE) buf[i] = '\0';
    i = 0;
    while (str2[i] != '\0' && i != MAX_STRING_SIZE)
    {
        str1[i] = str2[i];
        i++;
    }
    if (i != MAX_STRING_SIZE) str1[i] = '\0';
    i = 0;
    while (buf[i] != '\0' && i != MAX_STRING_SIZE)
    {
        str2[i] = buf[i];
        i++;
    }
    if (i != MAX_STRING_SIZE) str2[i] = '\0';
}
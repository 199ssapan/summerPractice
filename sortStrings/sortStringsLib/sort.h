#include <stdio.h>
#define MAX_STRINGS_COUNT 100
#define MAX_STRING_SIZE 50
int myStrlen(char* string);
char* generateString(unsigned maxSize);
char** generateStrings(unsigned count, unsigned maxStringSize);
FILE* getFileWRandStrings(char* filePath);
int ReadStringsToArrays(FILE* file, char staticArray[][MAX_STRING_SIZE], char*** dynamicArray);
char* myToLowerDynamic(char* str);
char* myToLowerStatic(char str[MAX_STRING_SIZE]);
int cmpByLexGraphOrderWOCaseStraight(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j);
int cmpByLexGraphOrderWOCaseReverse(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j);
int cmpByLexGraphOrderStraight(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j);
int cmpByLexGraphOrderReverse(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j);
int cmpByLenStraight(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j);
int cmpByLenReverse(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j);
void printStrings(char staticArray[][MAX_STRING_SIZE], char** dynamicArray);
void SortStrings (char staticStrings[][MAX_STRING_SIZE], char **dynamicStrings, int (*compareStringsFunction)(char staticArray[][MAX_STRING_SIZE], char** dynamicArray, int i, int j));
int lenStatic(char str[MAX_STRING_SIZE]);
int lenDynamic(char* str);
void swapStatic(char str1[MAX_STRING_SIZE], char str2[MAX_STRING_SIZE]);
void swapdynamic(char** f, char** s);
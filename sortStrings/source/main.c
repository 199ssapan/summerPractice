#include "/home/maxim/sortStrings/sortStringsLib/sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int (*func1)(char[][MAX_STRING_SIZE], char**, int, int) = cmpByLexGraphOrderReverse;
    int (*func2)(char[][MAX_STRING_SIZE], char**, int, int) = cmpByLexGraphOrderStraight;
    int (*func3)(char[][MAX_STRING_SIZE], char**, int, int) = cmpByLexGraphOrderWOCaseReverse;
    int (*func4)(char[][MAX_STRING_SIZE], char**, int, int) = cmpByLexGraphOrderWOCaseStraight;
    int (*func5)(char[][MAX_STRING_SIZE], char**, int, int) = cmpByLenStraight;
    int (*func6)(char[][MAX_STRING_SIZE], char**, int, int) = cmpByLenReverse;
    char* fileName = "/home/maxim/sortStrings/file.txt";
    FILE* file = getFileWRandStrings(fileName);
    file = fopen(fileName, "r");
    char staticArray[MAX_STRINGS_COUNT][MAX_STRING_SIZE];
    char** dynamicArray;
    ReadStringsToArrays(file, staticArray, &dynamicArray);
    printStrings(staticArray, dynamicArray);
    //swapdynamic(&dynamicArray[0], &dynamicArray[1]);
    //swapStatic(staticArray[0], staticArray[1]);
    printf("\n");
    SortStrings(staticArray, dynamicArray, func2);
    printStrings(staticArray, dynamicArray);
    // return 0;
}
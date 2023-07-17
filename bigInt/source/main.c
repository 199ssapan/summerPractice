#include "/home/maxim/sumPrac/bigInt/bigIntLib/bigInt.h"
#include <stdio.h>
#include <stdlib.h>
#define MEM_ALL_ERR "Memory allocation error\n"
#define WRONG_INPUT "Incorrect input\n"

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("Too few arguments\n");
        return 1;
    }
    bigInt* a = initializationBigInt(argv[1]);
    bigInt* b = initializationBigInt(argv[3]);
    if (a == NULL || b == NULL)
    {
        printf(MEM_ALL_ERR);
    }
    printf("a = ");
    print(a);
    printf("b = ");
    print(b);
    bigInt* c;
    printf("\n");
    if (argv[2][0] == '+')
        c = addition(a, b);
    else if (argv[2][0] == '-')
        c = substraction(a, b);
    else
    {
        printf(WRONG_INPUT);
        return 1;
    }
    if (c == NULL)
    {
        printf(MEM_ALL_ERR);
    }
    printf("c = ");
    print(c);
    freeAll(a);
    freeAll(b);
    freeAll(c);
    return 0;
}
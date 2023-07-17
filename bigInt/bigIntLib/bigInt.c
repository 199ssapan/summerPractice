#include "/home/maxim/sumPrac/bigInt/bigIntLib/bigInt.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bigInt *initializationBigInt(char *strNumber)
{
    bigInt *bigNum = (bigInt *)malloc(sizeof(bigInt));
    if (bigNum == NULL)
        return NULL;
    int isSign = 0;
    if (strNumber[0] == '-' || strNumber[0] == '+')
        isSign = 1;
    if (strNumber[0] == '-')
        bigNum->sign = -1;
    else
        bigNum->sign = 1;
    int lenNum = strlen(strNumber);
    int sizeWOExtraChars = (lenNum - isSign) / 8;
    int sizeofExtraChars = (lenNum - isSign) % 8;
    if (sizeofExtraChars == 0)
        bigNum->wordsCount = sizeWOExtraChars;
    else
        bigNum->wordsCount = sizeWOExtraChars + 1;
    char* buf = (char*)malloc(sizeof(char) * (8 + 1));
    bigNum->words = (unsigned*)malloc(sizeof(unsigned) * bigNum->wordsCount);
    int iter = 0;
    for (int i = 0; i < sizeWOExtraChars; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            buf[j] = *(strNumber + lenNum - (i + 1) * 8 + j);
        }
        buf[8] = '\0';
        bigNum->words[iter] = strtoul(buf, NULL, 16);
        iter++;
    }

    if (sizeofExtraChars != 0)
    {
        for (int i = 0; i < sizeofExtraChars; i++)
        {
            buf[i] = strNumber[lenNum - sizeWOExtraChars * 8 - sizeofExtraChars + i];
        }
        buf[sizeofExtraChars] = '\0';
        bigNum->words[iter] = strtoul(buf, NULL, 16);
    }
    for (int i = bigNum->wordsCount - 1; i > 0 && bigNum->words[i] == 0; i--)
    {
        bigNum->wordsCount--;
    }
    free(buf);
    return bigNum;
}

bigInt* sumPositive(bigInt *a, bigInt *b)
{
    bigInt *r = (bigInt *)malloc(sizeof(bigInt));
    int rWC;
    if (a->wordsCount > b->wordsCount)
        rWC = a->wordsCount;
    else
        rWC = b->wordsCount;
    r->wordsCount = rWC;
    r->words = (unsigned *)malloc(sizeof(unsigned) * r->wordsCount);
    int minWordsCount;
    if (a->wordsCount < b->wordsCount) minWordsCount = a->wordsCount;
    else minWordsCount = b->wordsCount;
    int itera = 0;
    int iterb = 0;
    for (int i = 0; i < r->wordsCount; i++)
    {
        r->words[i] = 0;
    }
    unsigned toNextDigit = 0;
    for (int i = 0; i < rWC; i++)
    {
        if (itera < minWordsCount && iterb < minWordsCount)
        {
            unsigned newNumber = a->words[i] + b->words[i] + r->words[i];
            if ((newNumber <= a->words[i] && b->words[i] != 0) || (newNumber <= b->words[i] && a->words[i] != 0))
            {
                toNextDigit = 1;
            }
            else
            {
                toNextDigit = 0;
            }
            r->words[i] = newNumber;
            if (toNextDigit == 1)
            {
                if (i == rWC - 1)
                {
                    if ((r->words = realloc(r->words, (rWC + 1) * sizeof(unsigned))) == NULL)
                    {
                        return NULL;
                    }
                    rWC++;
                }
                r->words[i + 1] = toNextDigit;
            }
            itera++;
            iterb++;
        }
      else  if (itera == a->wordsCount)
        {
            if (iterb < b->wordsCount + 1)
            {
                unsigned newNum = r->words[i] + b->words[i];
                if (newNum < r->words[i] || newNum < b->words[i])
                {
                    toNextDigit = 1;
                }
                else
                {
                    toNextDigit = 0;
                }
                if (toNextDigit)
                {
                    if (i == rWC - 1)
                    {
                        if ((r->words = realloc(r->words, (rWC + 1) * sizeof(unsigned))) == NULL)
                        {   
                            return NULL;
                        }
                        rWC++;
                    }
                    r->words[i + 1] = toNextDigit;
                }
                r->words[i] = r->words[i] + b->words[i];
                if (toNextDigit) r->words[i + 1] = toNextDigit;
                iterb++;
            }
        }
        else if (iterb == b->wordsCount)
        {
            if (iterb < a->wordsCount + 1)
            {
                unsigned newNum = r->words[i] + a->words[i];
                if (newNum < r->words[i] || newNum < a->words[i])
                {
                    toNextDigit = 1;
                }
                else
                {
                    toNextDigit = 0;
                }
                if (toNextDigit)
                {
                    if (i == rWC - 1)
                    {
                        if ((r->words = realloc(r->words, (rWC + 1) * sizeof(unsigned))) == NULL)
                        {   
                            return NULL;
                        }
                        rWC++;
                    }
                    r->words[i + 1] = toNextDigit;
                }
                r->words[i] = r->words[i] + a->words[i];
                if (toNextDigit) r->words[i + 1] = toNextDigit;
                itera++;
            }
        }
    }
    r->wordsCount = rWC;
    return r;
}

bigInt* subPositive(bigInt *a, bigInt *b)
{
    bigInt *r = (bigInt *)malloc(sizeof(bigInt));
    int rWC;
    if (a->wordsCount > b->wordsCount)
        rWC = a->wordsCount;
    else
        rWC = b->wordsCount;
    r->wordsCount = rWC;
    r->words = (unsigned *)malloc(sizeof(unsigned) * (r->wordsCount - 1));
    int minWordsCount;
    if (a->wordsCount < b->wordsCount) minWordsCount = a->wordsCount;
    else minWordsCount = b->wordsCount;
    int itera = 0;
    int iterb = 0;
    for (int i = 0; i < r->wordsCount; i++)
    {
        r->words[i] = 0;
    }
    unsigned toNextDigit = 0;
    for (int i = 0; i < rWC; i++)
    {
        if (itera < minWordsCount && iterb < minWordsCount)
        {
            unsigned newNumber = a->words[i] - b->words[i] + r->words[i];
            if (newNumber >= a->words[i] && b->words[i] != 0)
            {
                printf("hhh\n");
                toNextDigit = 1;
            }
            else
            {
                printf("kkk\n");
                toNextDigit = 0;
            }
            r->words[i] = newNumber;
            if (toNextDigit == 1)
            {
                if (i == rWC - 1)
                {
                    if ((r->words = realloc(r->words, (rWC + 1) * sizeof(unsigned))) == NULL)
                    {
                        return NULL;
                    }
                    rWC++;
                }
                r->words[i + 1] = -toNextDigit;
            }
            itera++;
            iterb++;
        }
      else  if (itera == a->wordsCount)
        {
            if (iterb < b->wordsCount + 1)
            {
                unsigned newNum = r->words[i] + b->words[i];
                if (newNum < b->words[i])
                {
                    toNextDigit = 1;
                }
                else
                {
                    toNextDigit = 0;
                }
                if (toNextDigit)
                {
                    if (i == rWC - 1)
                    {
                        if ((r->words = realloc(r->words, (rWC) * sizeof(unsigned))) == NULL)
                        {   
                            return NULL;
                        }
                        rWC++;
                    }
                    r->words[i + 1] = -toNextDigit;
                }
                r->words[i] = r->words[i] + b->words[i];
                if (toNextDigit) r->words[i + 1] = toNextDigit;
                iterb++;
            }
        }
        else if (iterb == b->wordsCount)
        {
            if (iterb < a->wordsCount + 1)
            {
                unsigned newNum = r->words[i] + a->words[i];
                if (newNum > a->words[i])
                {
                    toNextDigit = 1;
                }
                else
                {
                    toNextDigit = 0;
                }
                if (toNextDigit)
                {
                    if (i == rWC - 1)
                    {
                        if ((r->words = realloc(r->words, (rWC) * sizeof(unsigned))) == NULL)
                        {   
                            return NULL;
                        }
                        rWC++;
                    }
                    r->words[i + 1] = -toNextDigit;
                }
                r->words[i] = r->words[i] + a->words[i];
                if (toNextDigit) r->words[i + 1] = -toNextDigit;
                itera++;
            }
        }
    }
    for (int i = rWC - 1; i > 0 && r->words[i] == 0; i--)
    {
        rWC--;
    }
    r->wordsCount = rWC;
    return r;
}

int cmpAbs(bigInt *f, bigInt *s)
{
    if (f->wordsCount > s->wordsCount)
        return 1;
    else if (f->wordsCount < s->wordsCount)
        return 0;
    else
    {
        for (int i = f->wordsCount - 1; i >= 0; i--)
        {
            if (f->words[i] > s->words[i])
                return 1;
            else if (s->words[i] > f->words[i])
                return 0;
        }
    }
    return 2;
}

void print(bigInt* num)
{
    if (num->sign == -1) printf("-");

    int flagf = 0;
    for (int i = num->wordsCount - 1; i >= 0; i--)
    {
        if (flagf == 0) 
        {
            printf("%x ", num->words[num->wordsCount - 1]);
            flagf = 1;
        }
        else printf("%08x ", num->words[i]);
    }
    printf("\n");
}


bigInt* addition(bigInt* a, bigInt* b)
{
    bigInt* c;
    if (a->sign == 1 && b->sign == 1)
    {
        c = sumPositive(a, b);
        c->sign = 1;
    }
    else if (a->sign == 1 && b->sign == -1)
    {
        int resCmp = cmpAbs(a, b);
        if (resCmp == 1)
        {
            c = subPositive(a, b);
            c->sign = 1;
        }
        else if (resCmp == 0)
        {
            c = subPositive(b, a);
            c->sign = -1;
        }
        else
        {
            c = subPositive(a, b);
            c->sign = 1;
        }
    }
    else if (a->sign == -1 && b->sign == 1)
    {
        int resCmp = cmpAbs(a, b);
        if (resCmp == 1)
        {
            c = subPositive(a, b);
            c->sign = -1;
        }
        else if (resCmp == 0)
        {
            c = subPositive(b, a);
            c->sign = 1;
        }
        else
        {
            c = subPositive(b, a);
            c->sign = 1;
        }
    }
    else if (a->sign == -1 && b->sign == -1)
    {
        c = sumPositive(a, b);
        c->sign = -1;
    }
    return c;
}

bigInt* substraction(bigInt* a, bigInt* b)
{
    bigInt* c;
    if (a->sign == 1 && b->sign == 1)
    {
        int resCmp = cmpAbs(a, b);
        if (resCmp == 1)
        {
            c = subPositive(a, b);
            c->sign = 1;
        }
        else if (resCmp == 0)
        {
            c = subPositive(b, a);
            c->sign = -1;
        }
        else
        {
            c = subPositive(a, b);
            c->sign = 1;
        }
    }
    else if (a->sign == 1 && b->sign == -1)
    {
        c = sumPositive(a, b);
        c->sign = 1;
    }
    else if (a->sign == -1 && b->sign == 1)
    {
        c = sumPositive(a, b);
        c->sign = -1;
    }
    else
    {
        int resCmp = cmpAbs(a ,b);
        if (resCmp == 1)
        {
            c = subPositive(a, b);
            c->sign = -1;
        }
        else if (resCmp == 0)
        {
            c = subPositive(b, a);
            c->sign = 1;
        }
        else
        {
            c = subPositive(a, b);
            c->sign = 1;
        }
    }
    return c;
}

int checkInput(char* str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (!((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 70) || (str[i] >= 97 && str[i] <= 102)))
        {
            return 1;
        }
    }
    return 0;
}

void freeAll(bigInt* a)
{
    free(a->words);
    free(a);
    return;
}
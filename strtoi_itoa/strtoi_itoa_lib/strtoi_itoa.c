#include "strtoi_itoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int strtoi(const char *str, char **p, int *ret)
{
    if (myStrlen(str) == 0)
    {
        *p = (char*)str;
        return 0;
    }
    int isPrefix = 0;
    char charBase;
    int base = getBase(str, &isPrefix, &charBase);
    printf("Base:%d\n", base);
    char isNegative = str[0] == '-' ? 1 : 0;
    char isPlus = str[0] == '+' ? 1 : 0;
    if (base == -1)
    {
        printf("qqq");
        *p = (char*)(str + isNegative + isPlus);
        return 1;
    }
    int len = 0, mult = 1, result = 0;
    int multLimit = 2147483647 / base, rem = 2147483647 % base;
    if (isPrefix || isNegative || isPlus)
    {
        str += (isPrefix + isNegative + isPlus);
    }
    len = myStrlen(str);
    if (len == 0)
    {
        *p = (char*)str;
        return 1;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        int digit = getDigit(str[i], charBase);
        if (digit == -1)
        {
            *p = (char*)(str + i);
            return 1;
        }
        if (digit > INT_MAX / mult)
        {
            return 2;
        }
        int pre = digit * mult;
        if (mult >= multLimit)
        {
            if ((i != 0 && digit != 0 && result > rem) || (pre < mult && pre != 0))
            {
                return 2;
            }
        }
        else
        {
            mult = mult * base;
        }
        int z = pre + result;
        if (z < result)
        {
            if (z != (INT_MIN) || isNegative == 0)
            {
                return 2;
            }
        }
        result = z;
    }
    if (isNegative == 1) *ret = -1 * result;
    else *ret = result;
    return 0;
}

int getDigit(char c, char cbase)
{
    if (c >= cbase && cbase != '!')
    {
        return -1;
    }
    else if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        return c - 'a' + 36;
    else return -1;
}

int getBase(const char *str, int *isPrefix, char *retCharBase)
{
    char cbase = '0';
    if (str[0] == '-')
    {
        if (str[2] == 'x')
        {
            cbase = str[1];
            *isPrefix = 2;
        }
        else
        {
            cbase = 'A';
        }
    }
    else
    {
        if (str[1] == 'x')
        {
            cbase = str[0];
            *isPrefix = 2;
        }
        else
        {
            cbase = 'A';
        }
    }
    *retCharBase = cbase;
    if (cbase >= '2' && cbase <= '9')
    {
        return cbase - '0';
    }
    else if (cbase >= 'A' && cbase <= 'Z')
    {
        return cbase - 'A' + 10;
    }
    else if (cbase >= 'a' && cbase <= 'z')
    {
        return cbase - 'a' + 36;
    }
    else if (cbase == '!')
        return 62;
    else
        return -1;
}

unsigned myStrlen(const char *string)
{
    if (string == NULL)
        return 0;
    unsigned count = 0;
    for (int i = 0; string[i] != '\0'; i++)
        count++;
    return count;
}

int checkDigits(const char *string, char base)
{
    int len = myStrlen(string);
    for (int i = 0; i < len; i++)
    {
        if ((string[i] >= base || string[i] < 0) && base != '!')
        {
            printf("LLL\n");
            return i;
        }
        else
        {
            if (((string[i] >= '0' && string[i] <= '9') || (string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z')) == 0)
            {
                printf("kkk\n");
                return i;
            }
        }
    }
    return -1;
}

int myItoa(char *buf, int bufSize, int value, int p)
{
    int isNegative = (value < 0) ? 1 : 0;
    int valueBackup = value;
    if (bufSize < 0)
        return 0;
    if (p <= 1 || p >= 63)
        return 0;
    int count = 0;
    while (value != 0)
    {
        value /= p;
        count++;
    }
    if (buf == NULL)
        return count;
    char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char *newBuf = (char *)malloc(sizeof(int) * 8 + 1);
    int digit;
    int index = 0;
    value = valueBackup;
    if (value < 0)
    {
        value = -value;
    }
    
    while (value != 0)
    {
        digit = abs(value % p);
        newBuf[index] = alphabet[digit];
        value = abs(value / p);
        index++;
    }
    if (index > bufSize)
        return 0;
    if (isNegative == 1)
    {
        newBuf[index] = '-';
        index++;
    }
    for (int i = 0; i < index; i++)
    {
        buf[i] = newBuf[index - i - 1];
    }
    buf[index] = '\0';
    free(newBuf);
    return index;
}
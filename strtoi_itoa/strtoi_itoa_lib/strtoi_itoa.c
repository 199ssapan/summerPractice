#include "strtoi_itoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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
    char isNegative = str[0] == '-' ? 1 : 0;
    char isPlus = str[0] == '+' ? 1 : 0;
    if (base == -1)
    {
        printf("qqq");
        *p = (char*)(str + isNegative + isPlus);
        return 1;
    }
    int len = 0, mult = 1, result = 0;
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
    
    int intermediateResult = 0; int multXdigit = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        //check wrong digits
        int digit = getDigit(str[i], charBase);
        if (digit == -1)
        {
            *p = (char*)(str + i);
            return 1;
        }
        //check overflow
        multXdigit = digit * mult;

        //if (mult == 0) return 2;
        if (multXdigit != 0 && multXdigit / mult != digit)
        {
            if (multXdigit == (INT_MIN) && isNegative == 1)
            {
                *ret = (INT_MIN);
                return 0;
            }
            else
            {
                return 2;
            }
        }
        intermediateResult = (isNegative == 1) ? (-1) * multXdigit + result : multXdigit + result;
        if (isNegative == 0 && result > intermediateResult)
        {
            return 2;
        }
        if (isNegative == 1 && result < intermediateResult)
        {
            return 2;
        }
        int multTmp = mult * base;
        if (multTmp / base != mult) return 2;
        mult *= base;
        result = intermediateResult;
    //     if (digit > INT_MAX / mult)
    //     {   
    //         printf("digit: %d, mult: %d, base: %d\n", digit, mult, base);
    //         return 2;
    //     }
    //     int pre = digit * mult;
    //     if (mult >= (INT_MAX) / base)
    //     {
    //         if ((i != 0 && digit != 0 && result > (INT_MAX) % base) || (pre < mult && pre != 0))
    //         {
    //             return 2;
    //         }
    //     }
    //     else
    //     {
    //         mult = mult * base;
    //     }
    //     int z = pre + result;
        
    //     if ((z > result && isNegative == 1) || (z < result && isNegative == 0))
    //     {
    //         if (z != (INT_MIN) || isNegative == 0)
    //         {
    //             return 2;
    //         }
    //     }
    //     result = z;
    }
    *ret = result;
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
    if (count > bufSize) return 0;
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
    if (value == 0)
    {
        buf[index] = '0';
        buf[index + 1] = '\0';
        return 2; 
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

void testStrtoi()
{
    int* num = (int*)malloc(sizeof(int));
    char** p = (char**)malloc(sizeof(const char*));
    *p = (char*)malloc(sizeof(const char));
    char* str;
    int r;
    str = "-145";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Normal input:\n");
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "237";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "Ax237";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "-BxAAAA123";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "!xz";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "!xzz";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "!x10";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "zxABC";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "-1234567";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "-2x100";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "-5x12344321";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "-Gx198ACD";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    str = "LxAK123";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    printf("Wrong symbols:\n");
    str = "1234  12";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "AxA";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "-:x123456";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "-!x!!!";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "xxy";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "-789d78";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "-2x10000200100";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "!!!!!!x!!!!!!";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);
    printf("Overflow:\n");
    str = "5x1111111111110222222222222222222222204444444444444444444444444444444444444444";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "2147483648";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "-2147483649";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "2x1010101010101010010101001111111110111111";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "4x3232323232322323123123123123123123123123";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "!xzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "90000000000000000000000000000000000000000000000000000000000000000000000000000";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
    str = "2x100000000000000000000000000000000000000000000000000000000000000000000000000000000";
    printf("str:%s\n",str);
    r = strtoi(str, p, num);
    if (r == 1)
    {   
        printf("Address: %p\n", p);
    }
    printf("errorcode: %d\n", r);
}

void testItoa()
{
    printf("Test Itoa\n");
    char* buf = (char*)malloc(sizeof(char) * 33);
    int n = -2147483648;
    int a;
    a = myItoa(buf, 33, n, 2);
    printf("Count of writen chars: %d\n", a);
    printf("%d in base %d : ", n, 2);
    fwrite(buf, sizeof(char), a, stdout);
    printf("\n");
    n = -2147483648;
    a = myItoa(buf, 33, n, 10);
    printf("Count of writen chars: %d\n", a);
    printf("%d in base %d : ", n, 10);
    fwrite(buf, sizeof(char), a, stdout);
    printf("\n");
    n = 5;
    a = myItoa(buf, 33, n, 5);
    printf("Count of writen chars: %d\n", a);
    printf("%d in base %d : ", n, 5);
    fwrite(buf, sizeof(char), a, stdout);
    printf("\n");
    n = 62;
    a = myItoa(buf, 33, n, 62);
    printf("Count of writen chars: %d\n", a);
    printf("%d in base %d : ", n, 62);
    fwrite(buf, sizeof(char), a, stdout);
    printf("\n");
    n = 100;
    a = myItoa(buf, 33, n, 16);
    printf("Count of writen chars: %d\n", a);
    printf("%d in base %d : ", n, 16);
    fwrite(buf, sizeof(char), a, stdout);
    printf("\n");
    n = 1908;
    a = myItoa(buf, 33, n, 25);
    printf("Count of writen chars: %d\n", a);
    printf("%d in base %d : ", n, 25);
    fwrite(buf, sizeof(char), a, stdout);
    printf("\n");
    n = 0;
    a = myItoa(buf, 33, n, 32);
    printf("Count of writen chars: %d\n", a);
    printf("%d in base %d : ", n, 32);
    fwrite(buf, sizeof(char), a, stdout);
    printf("\n");
}
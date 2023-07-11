#include "passGen.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

char** getPasswords(int argc, char** argv, int* errCode, int* countPasswords)
{
    long long len = 0; long long minLen = 0; long long maxLen = 0;
    int nFlag = 0; int mFlag = 0; int MFlag = 0; int cFlag = 0; int aFlag = 0; int bigCFlag = 0;
    char* alpha = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp("-m1", argv[i]) == 0)
        {
            if (i != argc - 1)
            {
                if (strlen(argv[i + 1]) != 0  && atoll(argv[i + 1]) != 0 && mFlag == 0 && nFlag == 0)
                {
                    minLen = atoll(argv[i + 1]);
                    if (minLen > (INT_MAX))
                    {
                        printf("Too long length\n");
                        return NULL;
                    }
                    mFlag = 1;
                    i++;
                }
                else 
                {
                    if (strlen(argv[i + 1]) != 0  && atoll(argv[i + 1]) == 0)
                    {
                        printf("Length must be positive integer number\n");
                    }
                    else if (mFlag != 0)
                    {
                        printf("There should be only one \'-m1\' flag\n");
                    }   
                    else if (nFlag != 0)
                    {
                        printf("Options \'-m1\', \'-m2\' and \'-n\' are not compatible together\n");
                    }
                    else
                    {
                        printf("Length error\n");
                    }
                    *errCode = ERR_WITH_LENGTH;
                    return NULL;
                }
            }
            else
            {
                printf("There no argument for \'-m1\'\n");
                *errCode = ERR_WITH_LENGTH;
                return NULL;
            }
        }
        else if (strcmp("-m2", argv[i]) == 0)
        {
            if (i != argc - 1)
            {
                if (strlen(argv[i + 1]) != 0  && atoll(argv[i + 1]) != 0 && MFlag == 0 && nFlag == 0)
                {
                    maxLen = atoll(argv[i + 1]);
                    if (maxLen > (INT_MAX))
                    {
                        printf("Too long length\n");
                        return NULL;
                    }
                    MFlag = 1;
                    i++;
                }
                else 
                {
                    if (MFlag != 0)
                    {
                        printf("There should be only one \'-m2\\' flag\n");
                    }
                    else if (nFlag != 0)
                    {
                        printf("Options \'-m1\', \'-m2\' and \'-n\' are not compatible together\n");
                    }
                    else
                    {
                        printf("Length error\n");
                    }
                    *errCode = ERR_WITH_LENGTH;
                    return NULL;
                }
            }
            else
            {
                printf("There no argument for \'-m2\'\n");
                *errCode = ERR_WITH_LENGTH;
                return NULL;
            }
        }
        else if (strcmp("-n", argv[i]) == 0)
        {
            if (i != argc - 1)
            {
                if (strlen(argv[i + 1]) != 0 && atoll(argv[i + 1]) != 0 && MFlag == 0 && mFlag == 0 && nFlag == 0)
                {
                    len = atoll(argv[i + 1]);
                    if (len <= 0)
                    {
                        printf("Length must be positive integer number\n");
                        *errCode = ERR_WITH_LENGTH;
                        return NULL;
                    }
                    else if (len > (INT_MAX))
                    {
                        printf("Too long length\n");
                        *errCode = ERR_WITH_LENGTH;
                        return NULL;
                    }
                    nFlag = 1;
                    i++;
                }
                else 
                {
                    if (strlen(argv[i + 1]) != 0 && atoll(argv[i + 1]) == 0)
                    {
                        printf("Length must be positive integer number\n");
                    }
                    else if (MFlag != 0 || mFlag != 0)
                    {
                        printf("Options \'-m1\', \'-m2\' and \'-n\' are not compatible together\n");
                    }
                    else if (nFlag != 0)
                    {
                        printf("There should be only one \'-n\\' flag\n");
                    }
                    else
                    {
                        printf("Length error\n");
                    }
                    *errCode = ERR_WITH_LENGTH;
                    return NULL;
                }
            }
            else
            {
                printf("There no argument for \'-n\'\n");
                *errCode = ERR_WITH_LENGTH;
                return NULL;
            }
        }
        else if (strcmp("-c", argv[i]) == 0)
        {
            if (i != argc - 1)
            {
                if (strlen(argv[i + 1]) != 0 && atoll(argv[i + 1]) != 0 && cFlag == 0)
                {
                    *countPasswords = atoi(argv[i + 1]);
                    cFlag = 1;
                    i++;
                }
                else 
                {
                    if (cFlag != 0)
                    {
                        printf("There should be only one \'-c\' flag\n");
                    }
                    else if (strlen(argv[i + 1]) != 0 && atoll(argv[i + 1]) == 0)
                    {
                        printf("Passwords count must be positive integer number\n");
                    }
                    else
                    {
                        printf("Paswwords count error\n");
                    }
                    *errCode = ERR_WITH_LENGTH;
                    return NULL;
                }
            }
            else
            {
                printf("There no argument for \'-c\'\n");
                *errCode = ERR_WITH_PASSCOUNT;
                return NULL;
            }
        }
        else if (strcmp("-a", argv[i]) == 0)
        {
            if (i != argc - 1)
            {
                if (aFlag == 0 && bigCFlag == 0)
                {
                    alpha = argv[i + 1];
                    i++;
                    aFlag = 1;
                }
                else 
                {
                    if (aFlag != 0)
                    {
                        printf("There should be only one \'-a\\' flag\n");
                    }
                    else if (bigCFlag != 0)
                    {
                        printf("Options \'-a\' and \'-C\' are not compatible together\n");
                    }
                    else
                    {
                        printf("Alphabet error\n");
                    }
                    *errCode = ERR_WITH_ALPHA;
                    return NULL;
                }
               }
            else
            {
                printf("There no argument for \'-a\'\n");
                *errCode = ERR_WITH_ALPHA;
                return NULL;
            }
        }
        else if (strcmp("-C", argv[i]) == 0)
        {
            if (i != argc - 1)
            {
                if (aFlag == 0 && bigCFlag == 0)
                {
                    alpha = getAlphabet(argv[i + 1]);
                    if (alpha == NULL)
                    {
                        printf("Invalid characters in the alphabet\n");
                        return NULL;
                    }
                    i++;
                    bigCFlag = 1;
                }
                else 
                {
                    if (aFlag != 0)
                    {
                        printf("Options \'-a\' and \'-C\' are not compatible together\n");
                    }
                    else if (bigCFlag != 0)
                    {
                        printf("There should be only one \'-a\\' flag\n");
                    }
                    else
                    {
                        printf("Alphaber error\n");
                    }
                    *errCode = ERR_WITH_ALPHA;
                    return NULL;
                }
            }
            else 
            {
                printf("There no argument for \'-C\'\n");
                *errCode = ERR_WITH_ALPHA;
                return NULL;
            }
        }
    }
    if (mFlag != 0 && MFlag == 0)
    {
        printf("Гndefined maximum length\n");
        *errCode = ERR_WITH_LENGTH;
        return NULL;
    }
    if (minLen == 0 && mFlag == 1)
    {
        printf("Length must be positive integer number\n");
        *errCode = ERR_WITH_LENGTH;
        return NULL;
    }
    if (minLen < 0 || maxLen < 0)
    {
        printf("Length must be positive integer number\n");
        *errCode = ERR_WITH_LENGTH;
        return NULL;
    }
    if (minLen > maxLen)
    {
        printf("The maximum length must not be less than the minimum length\n");
        *errCode = ERR_WITH_LENGTH;
        return NULL;
    }
    if (nFlag == 1 && len <= 0)
    {
        printf("Length must be positive integer number\n");
        *errCode = ERR_WITH_LENGTH;
        return NULL;
    }
    if (*countPasswords == 0)
    {
        printf("Passwords count must be positive integer number\n");
        *errCode = ERR_WITH_PASSCOUNT;
        return NULL;
    }
    char** passwords = (char**)malloc(sizeof(char*) * (*countPasswords));
    if (passwords == NULL)
    {
        printf("Mem allocation error\n");
        *errCode = ERR_WITH_MEM_ALLOCATION;
        return NULL;
    }
    for (int i = 0; i < *countPasswords; i++)
    {
        passwords[i] = generatePassword(minLen, maxLen, len, alpha);
    }
    return passwords;
}

char* generatePassword(int minLen, int maxLen, int len, char* alphabet)
{
    int size;
    if (len != 0)
    {
        size = len;
    }
    else
    {
        if (minLen == maxLen)
        {
            size = maxLen;
        }
        else
        {
            size = rand() % (maxLen - minLen + 1) + minLen;
        }
    }
    char* pass = (char*)malloc(sizeof(char) * (size + 1));
    if (pass == NULL)
    {
        return NULL;
    }
    int alphaLen = strlen(alphabet);
    for (int i = 0; i < size; i++)
    {
        pass[i] = alphabet[rand() % alphaLen];
    }
    pass[size] = '\0';
    return pass;
}

char* getAlphabet(char* potenAlpha)
{
    int len = strlen(potenAlpha);
    if (len > 4) return NULL;
    int masCount[4] = {0};
    for (int i = 0; i < len; i++)
    {
        if (potenAlpha[i] == 'a') masCount[LOWER]++;
        else if (potenAlpha[i] == 'A') masCount[UPPER]++;
        else if (potenAlpha[i] == 'D') masCount[DIGIT]++;
        else if (potenAlpha[i] == 'S') masCount[SPECIAL]++;
        else return NULL;
    }
    for (int i = 0; i < 4; i++)
    {
        if (masCount[i] > 1) return NULL;
    }
    char upperCase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lowerCase[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    char specialSymbols[] = "!@#$\\%^&*()\"№;:?_-=+~|/[]{}\' ";
    char rawAlphabet[100] = "";
    if (masCount[LOWER]) strcat(rawAlphabet, lowerCase);
    if (masCount[UPPER]) strcat(rawAlphabet, upperCase);
    if (masCount[DIGIT]) strcat(rawAlphabet, digits);
    if (masCount[SPECIAL]) strcat(rawAlphabet, specialSymbols);
    char* alphabet = (char*)malloc(sizeof(char) * (strlen(rawAlphabet) + 1));
    for (int i = 0; i < strlen(rawAlphabet); i++)
        alphabet[i] = rawAlphabet[i];
    alphabet[strlen(rawAlphabet)] = '\0';
    return alphabet;
}

char* concat(char* f, char* s)
{
    int len1 = strlen(f);
    int len2 = strlen(f);                      
    char *result = malloc(len1 + len2 + 1);
    if (!result) 
    {
        return NULL;
    }
    memcpy(result, f, len1);
    memcpy(result + len1, s, len2 + 1);   
    result[len1 + len2] = '\0'; 
    return result;
}
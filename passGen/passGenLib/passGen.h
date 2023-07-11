#pragma once
char** getPasswords(int argc, char** argv, int* errCode, int* countPasswords);
char* concat(char* f, char* s);
char* getAlphabet(char* potenAlpha);
char* generatePassword(int minLen, int maxLen, int len, char* alphabet);

typedef enum alphaCount
{
    LOWER = 0,
    UPPER,
    DIGIT,
    SPECIAL
}alphaCount;

typedef enum ERR
{
    ERR_WITH_LENGTH = 1,
    ERR_WITH_ALPHA,
    ERR_WITH_PASSCOUNT,
    ERR_WITH_MEM_ALLOCATION
}ERR;

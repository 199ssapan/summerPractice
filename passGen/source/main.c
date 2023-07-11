#include "/home/maxim/passGen/passGenLib/passGen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        return 0;
    }
    setlocale(LC_ALL, "Rus");
    int p = time(0);
    srand((int)&p ^ p );
    int *er = (int*)malloc(sizeof(int));
    int countPasswords = 1;
    char** passwords = getPasswords(argc, argv, er, &countPasswords);
    if (passwords == NULL)
    {
        if (*er == ERR_WITH_ALPHA) printf("err_alpha\n");
        else if (*er == ERR_WITH_LENGTH) printf("err_length\n");
        else if (*er == ERR_WITH_PASSCOUNT) printf("err_passcount\n");
        for (int i = 0; i < countPasswords; i++)
        {
            free(passwords[i]);
        }
        free(passwords);
        return 0;
    }
    for (int i = 0; i < countPasswords; i++)
    {
        printf("%s\n", passwords[i]);
    }
    return 0;
}

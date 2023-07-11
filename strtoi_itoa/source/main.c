#include <stdio.h>
#include <malloc.h>
#include "/home/maxim/strtoi_itoa/strtoi_itoa_lib/strtoi_itoa.h"
#include <limits.h> 

int main()
{
    int* num = (int*)malloc(sizeof(int));
    char* str = "-Gx800000000";
    printf("str = %s\n", str);
    char** p = (char**)malloc(sizeof(const char*));
    *p = (char*)malloc(sizeof(const char));
    int r = strtoi(str, p, num);
    if (r != 0)
    {   
        printf("Address: %p\n", p);
    }
    printf("Number: %d, errorcode: %d\n", *num, r);

    // char* buf = (char*)malloc(sizeof(char) * 33);
    // int a = myItoa(buf, 33, 214748364, 11);
    // // for (int i = 0; i < a; i++)
    // // {
    // //     printf("^^%c", buf[i]);
    // // }
    // fwrite(buf, sizeof(char), a, stdout);
    
    return 0;
}
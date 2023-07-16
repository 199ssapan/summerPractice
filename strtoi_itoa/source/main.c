#include <stdio.h>
#include <malloc.h>
#include "/home/maxim/sumPrac/strtoi_itoa/strtoi_itoa_lib/strtoi_itoa.h"
#include <limits.h> 

int main(int argc, char* argv[])
{
    int* num = (int*)malloc(sizeof(int));
    char** p = (char**)malloc(sizeof(const char*));
    *p = (char*)malloc(sizeof(const char));
    // char* str = "";
    // int r = strtoi(str, p, num);
    // if (r == 1)
    // {   
    //     printf("Address: %p\n", p);
    // }
    // printf("Number: %d, errorcode: %d\n", *num, r);
    testStrtoi();
    testItoa();
    // int a = strtoi("Gx800000000", p, num);
    // if (a == 2)
    // {
    //     printf("OverFlow");
    // }
    
    return 0;
}
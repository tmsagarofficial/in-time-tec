#include <limits.h>
#include<stdio.h>
int main() 
{
    int *ptr;
    *ptr = 66;
    char *ch_ptr;
    ch_ptr = (char*)ptr;
    printf("%c", *ch_ptr);

    return 0;
}
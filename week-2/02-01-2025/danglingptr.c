#include <stdio.h>  
int main()  
{  
    int a=1;
    int *ptr=(int *)malloc(sizeof(int));
    ptr=&a;  
    free(ptr);  
    return 0;  
}  
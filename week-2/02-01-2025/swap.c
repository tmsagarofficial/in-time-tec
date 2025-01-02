#include<stdio.h>

void swapUsingThirdVariable(int *, int *);
void swapWithoutUsingVariable(int *, int *);

void swapUsingThirdVariable(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swapWithoutUsingVariable(int *a, int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}


int main(){
    int a=5,b=10;
    printf("Using Third Variable\n");
    printf("Before Swapping: a:%d, b:%d\n",a,b);
    swapUsingThirdVariable(&a,&b);
    printf("After Swapping: a:%d, b:%d\n\n",a,b);


    printf("Before Using Third Variable\n");
    printf("Before Swapping: a:%d, b:%d\n",a,b);
    swapWithoutUsingVariable(&a,&b);
    printf("After Swapping: a:%d, b:%d\n",a,b);

    return 0;
}
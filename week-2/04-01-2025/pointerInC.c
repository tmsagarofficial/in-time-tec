#include <stdio.h>

void update(int *a,int *b) {
    int aa=*a;
    *a=*a+*b;
    if(aa>*b) *b=aa-*b;
    else *b=*b-aa;    
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
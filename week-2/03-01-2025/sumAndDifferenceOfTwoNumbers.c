#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	int a,b;
    scanf("%d %d",&a,&b);
    float c,d;
    scanf("%f %f",&c,&d);
    printf("%d %d\n",(a+b),(a-b));
    printf("%0.1f %0.1f",(c+d),(c-d));
    
    return 0;
}
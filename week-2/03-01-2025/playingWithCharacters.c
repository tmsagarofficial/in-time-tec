#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    char ch;
    scanf("%c",&ch);
    char s[100];
    scanf("\n");
    scanf("%[^\n]%*c",s);
    char sen[100];
    scanf("%[^\n]%*c",sen);
    printf("%c\n%s\n%s",ch,s,sen);
    return 0;
}
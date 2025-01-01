#include<stdio.h>

long long solve(int b,int n,int m);
long long solve(int b,int n,int m){

   if (n == 0) 
       return 1%m;
   long long val = solve(b,n/2,m);                                              
   val = (val*val)%m;
   if (n%2 == 1) 
       val = (val*b)%m;
   return val;
}
int main(){

    int b,n,m;
    scanf("%d %d %d",&b,&n,&m);
    if(m>1&&n>=0&&b>0&&n<=1000000000000000&&m<=1000000000000000){
        printf("%lld",solve(b,n,m));
    }else{
        printf("Invalid Input");
    }
    
    return 0;
}
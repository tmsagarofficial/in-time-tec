#include <stdio.h>


int max(int a, int b);

int max_of_four(int a, int b, int c, int d) {
    int l, r;
    l = max(a, b);
    r = max(c, d);
    return max(l, r);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);
    
    return 0;
}

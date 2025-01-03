#include <stdio.h>

int main() {
    char method1a[12] = {'K', 'a', 'l', 'p', 'a', 'v', 'r', 'i', 'k', 's', 'h', 'a'};
    char method1b[13] = {'K', 'a', 'l', 'p', 'a', 'v', 'r', 'i', 'k', 's', 'h', 'a','\0'};
    char method2[] = "Kalpavriksha";
    const char *method3 = "Kalpavriksha";     

    printf("Address and size of method1a: %p %zu\n", method1a, sizeof(method1a));
    printf("Address and size of method1b: %p %zu\n", method1b, sizeof(method1b));
    printf("Address and size of method2: %p %zu\n", method2, sizeof(method2));
    printf("Address and size of method3: %p %zu\n", method3, sizeof(method3));

    printf("method1a: %s\n", method1a);
    printf("method1b: %s\n", method1b);
    printf("method2: %s\n", method2);
    printf("method3: %s\n", method3);
    return 0;
}

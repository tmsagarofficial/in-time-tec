#include <stdio.h>

int main() {
    int x = 10, y = 20;

    const int* ptr1 = &x;

    printf("Case 1: Pointer to a constant value\n");
    printf("Initial value of x: %d\n", *ptr1);

    ptr1 = &y;
    printf("New value pointed to by ptr1 (y): %d\n", *ptr1);

    int* const ptr2 = &x;

    printf("\nCase 2: Constant pointer\n");
    printf("Initial value of x: %d\n", *ptr2);

    *ptr2 = 15;
    printf("New value of x (after modification via ptr2): %d\n", *ptr2);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct item_t {
    char item_name[20];
    int item_cost;
} item;

item cart[50];

int main() {
    int n, totalCost = 0;

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        char line[50];
        fgets(line, sizeof(line), stdin);

        char* token = strtok(line, ",");
        strncpy(cart[i].item_name, token, 20 - 1);
        cart[i].item_name[20 - 1] = '\0';

        token = strtok(NULL, ",");
        cart[i].item_cost = atoi(token);

        totalCost += cart[i].item_cost;
    }

    printf("item list\n");
    for (int i = 0; i < n; i++) {
        printf("%s,%d\n", cart[i].item_name, cart[i].item_cost);
    }

    printf("Total cost %d\n", totalCost);

    printf("item quantities\n");
    int counted[50] = {0};
    for (int i = 0; i < n; i++) {
        int quantity = 1;

        if (counted[i] == 1) {
            continue;
        }


        for (int j = i + 1; j < n; j++) {
            if (strcmp(cart[i].item_name, cart[j].item_name) == 0) {
                quantity++;
                counted[j] = 1;
            }
        }


        printf("%s - %d\n", cart[i].item_name, quantity);
    }
    return 0;
}

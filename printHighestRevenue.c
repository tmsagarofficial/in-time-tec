#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    getchar();

    char companyNames[100][50];
    long long companyRevenues[100];
    long long maxRevenue = 0;

    for (int i = 0; i < m; i++) {
        scanf("%s", companyNames[i]);
        long long totalRevenue = 0;
        for (int j = 0; j < n; j++) {
            long long revenue;
            scanf("%lld", &revenue);
            totalRevenue += revenue;
        }
        companyRevenues[i] = totalRevenue;
        if (totalRevenue > maxRevenue) {
            maxRevenue = totalRevenue;
        }
    }

    for (int i = 0; i < m; i++) {
        if (companyRevenues[i] == maxRevenue) {
            printf("%s\n", companyNames[i]);
        }
    }

    return 0;
}

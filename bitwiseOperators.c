#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void calculate_the_maximum(int n, int k)
{
    int i, j, and, maxAnd = 0, or, maxOr = 0, xor, maxXor = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = i + 1; j <= n; j++)
        {
            and = i & j;
            if (and > maxAnd && and < k)
            {
                maxAnd = and;
            }

            or = i | j;
            if (or > maxOr && or < k)
            {
                maxOr = or ;
            }

            xor = i ^ j;
            if (xor > maxXor && xor < k)
            {
                maxXor = xor;
            }
        }
    }
    printf("%d\n%d\n%d\n", maxAnd, maxOr, maxXor);
}

int main()
{
    int n, k;

    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);

    return 0;
}

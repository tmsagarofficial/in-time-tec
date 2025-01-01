#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{

    int n, temp;
    scanf("%d", &n);
    int meals[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &meals[i]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (meals[i] > meals[j])
            {
                temp = meals[i];
                meals[i] = meals[j];
                meals[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", meals[i]);
    }
    return 0;
}

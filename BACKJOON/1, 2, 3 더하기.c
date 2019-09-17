#include <stdio.h>

int main(void)
{
    int N;
    int c[15];
    int D[15];

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &c[i]);
    }

    //init
    D[1] = 1;
    D[2] = 2;
    D[3] = 4;

    for (int i = 4; i < 11; i++)
    {
        D[i] = D[i - 3] + D[i - 2] + D[i - 1];
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d\n", D[c[i]]);
    }

    return 0;
}
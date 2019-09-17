#include <stdio.h>
#define INIT_VALUE -1

int a[100050];

void teleportSet(int index, int value, int K)
{
    if (index < 0)
        return;

    while (index <= 2 * K)
    {
        if (a[index] == INIT_VALUE)
            a[index] = value;
        else if (a[index] > value)
            a[index] = value;

        index *= 2;
    }
}

int main(void)
{
    int N, K;
    int Answer = 0;

    scanf("%d%d", &N, &K);

    if (N >= K)
    {
        Answer = N - K;
        printf("%d", Answer);
        return 0;
    }

    for (int i = 0; i < 2 * K; i++)
    {
        a[i] = INIT_VALUE;
    }

    a[N] = 0;

    for (int i = 1; i < K - N; i++)
    {
        teleportSet(N + i, a[N] + i);
        teleportSet(N - i, a[N] - i);
    }

    return 0;
}
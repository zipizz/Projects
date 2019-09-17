#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N;
    int *H; // height
    int *R; // received number

    int maxIndex;

    scanf("%d", &N);

    H = (int *)malloc(sizeof(int) * N);
    R = (int *)malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &H[i]);
    }

    R[0] = 0;
    maxIndex = 0;

    for (int i = 1; i < N; i++)
    {
        if (H[i - 1] > H[i])
        {
            R[i] = i;
            continue;
        }

        if (H[maxIndex] < H[i])
        {
            R[i] = 0;
            maxIndex = i;
            continue;
        }

        int j = R[i - 1];

        while (H[j - 1] < H[i] && j)
        {
            j = R[j - 1];
        }

        R[i] = j;
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d ", R[i]);
    }

    free(H);
    free(R);

    return 0;
}
#include <stdio.h>

int MAX(int a, int b)
{
    return a > b ? a : b;
}

int main(void)
{
    int N;

    int a[550][2];
    int DP[550];

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d%d", &a[i][0], &a[i][1]);
    }

    for (int i = 0; i < N; i++)
    {
        int min = a[i][0];
        int location = i;
        for (int j = i + 1; j < N; j++)
        {
            if (min > a[j][0])
            {
                min = a[j][0];
                location = j;
            }
        }

        int temp1 = a[i][0];
        int temp2 = a[i][1];

        a[i][0] = a[location][0];
        a[location][0] = temp1;

        a[i][1] = a[location][1];
        a[location][1] = temp2;
    }

    int Answer = 1;

    DP[0] = 1;

    for (int i = 1; i < N; i++)
    {
        DP[i] = 1;

        for (int j = 0; j < i; j++)
        {
            if (a[j][1] < a[i][1])
            {
                DP[i] = MAX(DP[i], DP[j] + 1);
            }
        }

        if (Answer < DP[i])
        {
            Answer = DP[i];
        }
    }

    Answer = N - Answer;

    printf("%d", Answer);

    return 0;
}
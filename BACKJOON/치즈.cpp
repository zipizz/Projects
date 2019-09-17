#include <stdio.h>

int Cheese[105][105];

void makeInternal(int i, int j, int N, int M)
{
    if (i < 0 || i >= N || j < 0 || j >= M || (Cheese[i][j] == 1) || (Cheese[i][j] == -1))
    {
        return;
    }

    Cheese[i][j] = -1;

    makeInternal(i + 1, j, N, M);
    makeInternal(i - 1, j, N, M);
    makeInternal(i, j + 1, N, M);
    makeInternal(i, j - 1, N, M);
}

int disapperChse(int chseCnt, int N, int M)
{
    for (int i = 1; i < N - 1; i++)
    {
        for (int j = 1; j < M - 1; j++)
        {
            if (Cheese[i][j] != 1)
                continue;

            int extnCnt = 0;
            if (Cheese[i + 1][j] == -1)
                extnCnt++;
            if (Cheese[i - 1][j] == -1)
                extnCnt++;
            if (Cheese[i][j + 1] == -1)
                extnCnt++;
            if (Cheese[i][j - 1] == -1)
                extnCnt++;
            if (extnCnt >= 2)
            {
                Cheese[i][j] = 0;
                chseCnt--;
            }
        }
    }
    return chseCnt;
}

void init(int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (Cheese[i][j] == -1)
                Cheese[i][j] = 0;
        }
    }
}

int main(void)
{
    int N, M;
    int chseCnt = 0;
    int Answer = 0;

    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            scanf("%d", &Cheese[i][j]);
            if (Cheese[i][j] == 1)
                chseCnt++;
        }
    }

    while (chseCnt)
    {
        // 외부공기 = -1, 내부공기 = 0
        makeInternal(0, 0, N, M);
        chseCnt = disapperChse(chseCnt, N, M);
        Answer++;
        init(N, M);
    }

    printf("%d", Answer);

    return 0;
}
#include <iostream>
#include <stdio.h>

using namespace std;

struct linked_list
{
    int node[105];
    int num[105];
    int count = 0;
    bool chk = false;
};

struct node
{
    int X;
    int Y;
    int K;
};

int Answer[105] = {0};
node inputPart[105];
bool isElement[105];
linked_list list[105];

void DFS(int x, int k, int M)
{
    // printf("DFS x,k,M : <%d,%d,%d> 시작\n", x, k, M);

    if (list[x].chk)
    {
        // printf("list[%d] chked O\n", x);
        for (int i = 0; i < list[x].count; i++)
        {
            // printf("Answer[list[%d].node[%d]] = %d, plus = %d * list[%d].num[%d] = %d\n", x, i, Answer[list[x].node[i]], k, x, i, k * list[x].num[i]);
            Answer[list[x].node[i]] += (k * list[x].num[i]);
        }
        return;
    }

    for (int i = M - 1, j = 0; i >= 0; i--)
    {
        if (inputPart[i].X != x)
            continue;

        // printf("insert X, Y, K : <%d, %d, %d>, current = %d, plus = %d\n", x, inputPart[i].Y, inputPart[i].K, Answer[inputPart[i].Y], k * inputPart[i].K);

        if (isElement[inputPart[i].Y])
        {
            Answer[inputPart[i].Y] += (k * inputPart[i].K);
            list[x].node[j] = inputPart[i].Y;
            list[x].num[j++] = inputPart[i].K;
            list[x].count++;
            list[x].chk = true;
            // printf("list[%d].node[%d], num[%d] = <%d,%d>, count = %d\n", x, j - 1, j - 1, list[x].node[j - 1], list[x].num[j - 1], list[x].count);
            continue;
        }

        list[x].chk = false;
        DFS(inputPart[i].Y, k * inputPart[i].K, M);
        // list[x].node[j] = inputPart[i].Y;
        // list[x].num[j++] = inputPart[i].K;
        // list[x].count++;
        // printf("list[%d].node[%d], num[%d] = <%d,%d>, count = %d\n", x, j - 1, j - 1, list[x].node[j - 1], list[x].num[j - 1], list[x].count);
    }
}

int main(void)
{
    int N, M;

    scanf("%d%d", &N, &M);

    for (int i = 0; i <= N; i++)
    {
        isElement[i] = true;
    }

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         Need[i][j] = 0;
    //     }
    // }

    for (int i = 0; i < M; i++)
    {
        scanf("%d%d%d", &inputPart[i].X, &inputPart[i].Y, &inputPart[i].K);
        isElement[inputPart[i].X] = false;
        //    Need[inputPart[i].X - 1][inputPart[i].Y - 1] = inputPart[i].K;
    }

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%d ", Need[i][j]);
    //     }
    //     printf("\n");
    // }

    // for (int i = 0; i < M; i++)
    // {
    //     if (isElement[inputPart[i].X])
    //         continue;

    //     if (isElement[inputPart[i].Y])
    //         continue;

    //     // printf("여기 : <%d,%d>\n", inputPart[i].X, inputPart[i].Y);
    //     int tmp1 = inputPart[i].Y;
    //     int tmp2 = inputPart[i].K;

    //     for (int j = 0; j < N; j++)
    //     {
    //         if (Need[tmp1 - 1][j] == 0)
    //             continue;

    //         if (!isElement[j])
    //             continue;

    //         Need[inputPart[i].X - 1][j] += tmp2 * Need[tmp1 - 1][j];

    //         // printf("Need[%d][%d] = %d\n", inputPart[i].X - 1, j, Need[inputPart[i].X - 1][j]);
    //     }

    //     Need[inputPart[i].X - 1][inputPart[i].Y - 1] = 0;
    // }

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%d ", Need[i][j]);
    //     }
    //     printf("\n");
    // }

    // for (int i = 1; i < N; i++)
    // {
    //     if (isElement[i])
    //     {
    //         printf("%d %d\n", i, Need[N - 1][i - 1]);
    //     }
    // }

    DFS(N, 1, M);

    for (int i = 1; isElement[i]; i++)
    {
        cout << i << " " << Answer[i] << endl;
    }

    return 0;
}

// 7
// 8
// 5 1 2
// 5 2 2
// 7 5 2
// 6 5 2
// 6 3 3
// 6 4 4
// 7 6 3
// 7 4 5
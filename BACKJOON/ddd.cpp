#include <iostream>
#include <stdio.h>

using namespace std;

struct node
{
    int X;
    int Y;
    int K;
};

int Answer[105] = {0};
node inputPart[105];
bool isElement[105];

void DFS(int y, int k, int M)
{
    for (int i = M - 1; i >= 0; i--)
    {
        if (inputPart[i].X != y)
            continue;

        if (isElement[inputPart[i].Y])
        {
            Answer[inputPart[i].Y] += (k * inputPart[i].K);
            continue;
        }

        DFS(inputPart[i].Y, k * inputPart[i].K, M);
    }
}

int main(void)
{
    int N, M;

    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++)
    {
        isElement[i] = true;
    }

    for (int i = 0; i < M; i++)
    {
        scanf("%d%d%d", &inputPart[i].X, &inputPart[i].Y, &inputPart[i].K);
        isElement[inputPart[i].X] = false;
    }

    DFS(N, 1, M);

    for (int i = 1; isElement[i]; i++)
    {
        cout << i << " " << Answer[i] << endl;
    }

    return 0;
}
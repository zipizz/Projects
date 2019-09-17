#include <stdio.h>

int N, M;
int SET[105];

int find(int x)
{
    while (SET[x] > 0)
    {
        x = SET[x];
    }

    return x;
}

void sortArr(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int arrTarget = arr[i];
        int j;

        for (j = i - 1; j >= 0 && arrTarget < arr[j]; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = arrTarget;
    }
}

void sortTwoArr(int arrFront[], int arrRear[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int arrTargetFront = arrFront[i];
        int arrTargetRear = arrRear[i];
        int j;

        for (j = i - 1; j >= 0 && arrTargetFront < arrFront[j]; j--)
        {
            arrFront[j + 1] = arrFront[j];
            arrRear[j + 1] = arrRear[j];
        }

        arrFront[j + 1] = arrTargetFront;
        arrRear[j + 1] = arrTargetRear;
    }
}

int main(void)
{
    int groupCnt = 0;  // ����ȸ�� ��
    int groupNum[105]; // ����ȸ�� ��� ��
    int groupFirst[105];
    int from[10000];
    int to[10000];
    int Answer[105];

    scanf("%d%d", &N, &M);

    for (int i = 0; i < 105; i++)
    {
        SET[i] = -1;
    }

    for (int i = 0; i < M; i++)
    {
        scanf("%d%d", &from[i], &to[i]);
        if (from[i] > to[i])
        {
            int temp = from[i];
            from[i] = to[i];
            to[i] = temp;
        }
    }

    // printf("\nsort Before\n");
    // for (int i = 0; i < M; i++)
    // {
    //     printf("FromTo : <%d,%d>\n", from[i], to[i]);
    // }

    sortTwoArr(from, to, M);

    // printf("\nsort After\n");
    // for (int i = 0; i < M; i++)
    // {
    //     printf("FromTo : <%d,%d>\n", from[i], to[i]);
    // }

    for (int i = 0; i < M; i++)
    {
        int ancestor;

        if (SET[to[i]] > 0)
        {
            if (SET[from[i]] > 0)
            {
                int fromAncestor = SET[from[i]];
                int toAncestor = SET[to[i]];
                int smallAncestor, bigAncestor;

                if (fromAncestor < toAncestor)
                {
                    smallAncestor = fromAncestor;
                    bigAncestor = toAncestor;
                }
                else if (fromAncestor == toAncestor)
                {
                    continue;
                }
                else
                {
                    smallAncestor = toAncestor;
                    bigAncestor = fromAncestor;
                }

                SET[smallAncestor] += SET[bigAncestor];
                SET[bigAncestor] = smallAncestor;

                for (int j = 1; j <= N; j++)
                {
                    if (SET[j] == bigAncestor)
                    {
                        SET[j] = smallAncestor;
                    }
                }
            }
            else
            {
                int parent = SET[to[i]];
                SET[from[i]] = parent;
                SET[parent]--;
            }
            continue;
        }

        ancestor = find(from[i]);
        SET[to[i]] = ancestor;
        SET[ancestor]--;
    }

    // for (int i = 1; i <= N; i++)
    // {
    //     printf("%3d", i);
    // }

    // printf("\n");

    // for (int i = 1; i <= N; i++)
    // {
    //     printf("%3d", SET[i]);
    // }

    // printf("\n");

    for (int i = 1; i <= N; i++)
    {
        if (SET[i] < 0)
        {
            groupFirst[groupCnt] = i;
            groupNum[groupCnt++] = -SET[i];
        }
    }

    printf("%d\n", groupCnt);
    // for (int i = 0; i < groupCnt; i++)
    // {
    //     printf("groupCnt[%d] = %d\n", i, groupNum[i]);
    // }

    for (int i = 0; i < groupCnt; i++)
    {
        int Floyd[100][100];

        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < 100; k++)
            {
                Floyd[j][k] = 10000;
            }
        }

        int members[100];
        int mCount = 0;

        for (int j = 1; j <= N; j++)
        {
            int k;

            if (SET[j] < 0)
            {
                k = j;
            }
            else
            {
                k = SET[j];
            }

            if (groupFirst[i] != k)
                continue;

            // printf("����� ���ܴ�ǥ k : %d\n", k);
            // printf("members[%d] = %d\n", mCount, j);
            members[mCount++] = j;
        }

        for (int j = 0; j < M; j++)
        {
            int k;

            if (SET[from[j]] < 0)
            {
                k = from[j];
            }
            else
            {
                k = SET[from[j]];
            }

            if (groupFirst[i] != k)
                continue;

            int x, y;

            for (int k = 0; k < mCount; k++)
            {
                if (from[j] == members[k])
                {
                    x = k;
                }
                if (to[j] == members[k])
                {
                    y = k;
                }
            }

            Floyd[x][y] = 1;
            Floyd[y][x] = 1;
        }

        // for (int j = 0; j < groupNum[i]; j++)
        // {
        //     for (int k = 0; k < groupNum[i]; k++)
        //     {
        //         printf("%d ", Floyd[j][k]);
        //     }
        //     printf("\n");
        // }

        for (int l = 0; l < groupNum[i]; l++)
        {
            for (int m = 0; m < groupNum[i]; m++)
            {
                for (int n = 0; n < groupNum[i]; n++)
                {
                    if (Floyd[n][m] > Floyd[n][l] + Floyd[l][m])
                    {
                        Floyd[n][m] = Floyd[n][l] + Floyd[l][m];
                    }
                }
            }
        }

        for (int j = 0; j < groupNum[i]; j++)
        {
            Floyd[j][j] = 0;
        }

        // printf("\n\n �ٲ� �� \n");
        // for (int j = 0; j < groupNum[i]; j++)
        // {
        //     for (int k = 0; k < groupNum[i]; k++)
        //     {
        //         printf("%d ", Floyd[j][k]);
        //     }
        //     printf("\n");
        // }

        int minIdx = 0;
        int min = 10001;
        for (int j = 0; j < groupNum[i]; j++)
        {
            int max = 0;
            for (int k = 0; k < groupNum[i]; k++)
            {
                if (max < Floyd[j][k])
                {
                    max = Floyd[j][k];
                }
            }
            // printf("\n%d° �� max : %d\n", j, max);
            if (min > max)
            {
                min = max;
                minIdx = j;
            }
        }

        Answer[i] = members[minIdx];
    }

    sortArr(Answer, groupCnt);

    for (int i = 0; i < groupCnt; i++)
    {
        printf("%d\n", Answer[i]);
    }
    return 0;
}

// �Է�
// ù° �߿� ȸ�ǿ� �����ϴ� ����� �� N�� �־�����. �����ڵ��� 1���� N������ �ڿ����� ǥ���Ǹ� ȸ�ǿ� �����ϴ� �ο��� 100 �����̴�. ��° �ٿ��� ���� �˰� �ִ� ������ �� M�� �־�����. �̾� M���� �� �ٿ��� ���� �ƴ� ������ �����ڸ� ��Ÿ���� �ΰ��� �ڿ����� �־�����.

// ���
// ù° �ٿ��� �����Ǵ� ����ȸ�� �� K�� ����Ѵ�. ���� K�ٿ��� �� ����ȸ�� ��ǥ ��ȣ�� ���� ������ ���ʷ� �� �ٿ� �ϳ��� ����Ѵ�. �� ����ȸ�� ��ǥ�� �� �� �ִ� ����� �� �̻��� ��� ���� �� �� ����ϸ� �ȴ�.

// ���� �Է� 1
// 8
// 7
// 1 2
// 2 3
// 4 5
// 5 6
// 4 6
// 6 7
// 7 4
// ���� ��� 1
// 3
// 2
// 4
// 8
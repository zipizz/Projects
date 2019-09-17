#include <stdio.h>

int a[105][105];

int DFS(int i, int j, int h, int n)
{
    if (i < 0 || i >= n || j < 0 || j >= n || a[i][j] < h)
        return 0;

    a[i][j] = h - 1;
    DFS(i + 1, j, h, n);
    DFS(i - 1, j, h, n);
    DFS(i, j + 1, h, n);
    DFS(i, j - 1, h, n);

    return 1;
}

int main(void)
{
    int N;
    int maxH = 0;
    int Answer = 0;
    int temp[105][105];

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &a[i][j]);
            temp[i][j] = a[i][j];

            if (maxH < a[i][j])
            {
                maxH = a[i][j];
            }
        }
    }

    for (int h = maxH; h > 0; h--)
    {
        int cnt = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (DFS(i, j, h, N))
                {
                    cnt++;
                }
            }
        }

        if (Answer < cnt)
        {
            Answer = cnt;
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                a[i][j] = temp[i][j];
            }
        }
    }

    printf("%d", Answer);

    return 0;
}

// ù° �ٿ��� � ������ ��Ÿ���� 2���� �迭�� ��� ���� ������ ��Ÿ���� �� N�� �Էµȴ�. N�� 2 �̻� 100 ������ �����̴�. ��° �ٺ��� N���� �� �ٿ��� 2���� �迭�� ù ��° ����� N��° ����� ������� �� �྿ ���� ������ �Էµȴ�. �� �ٿ��� �� ���� ù ��° ������ N��° ������ N���� ���� ������ ��Ÿ���� �ڿ����� �� ĭ�� ���̿� �ΰ� �Էµȴ�. ���̴� 1�̻� 100 ������ �����̴�.

// ���
// ù° �ٿ� �帶ö�� ���� ����� �ʴ� ������ ������ �ִ� ������ ����Ѵ�.

// ���� �Է� 1
// 5
// 6 8 2 6 2
// 3 2 3 4 6
// 6 7 3 3 2
// 7 2 5 3 6
// 8 9 5 2 7
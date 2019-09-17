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

// 첫째 줄에는 어떤 지역을 나타내는 2차원 배열의 행과 열의 개수를 나타내는 수 N이 입력된다. N은 2 이상 100 이하의 정수이다. 둘째 줄부터 N개의 각 줄에는 2차원 배열의 첫 번째 행부터 N번째 행까지 순서대로 한 행씩 높이 정보가 입력된다. 각 줄에는 각 행의 첫 번째 열부터 N번째 열까지 N개의 높이 정보를 나타내는 자연수가 빈 칸을 사이에 두고 입력된다. 높이는 1이상 100 이하의 정수이다.

// 출력
// 첫째 줄에 장마철에 물에 잠기지 않는 안전한 영역의 최대 개수를 출력한다.

// 예제 입력 1
// 5
// 6 8 2 6 2
// 3 2 3 4 6
// 6 7 3 3 2
// 7 2 5 3 6
// 8 9 5 2 7
#include <stdio.h>

int main(void)
{
    int N;
    int M;

    int DP[45][45];
    int VIP[45];

    scanf("%d%d", &N, &M);

    for (int i = 0; i < M; i++)
    {
        scanf("%d", &VIP[i]);
    }

    if (M == 0)
    {
        DP[0][0] = N;
    }
    else
    {
        DP[0][0] = VIP[0] - 1;
        DP[M][0] = N - VIP[M - 1];
    }

    for (int i = 1; i < M; i++)
    {
        DP[i][0] = VIP[i] - VIP[i - 1] - 1;
    }

    // for (int i = 0; i <= M; i++)
    // {
    //     printf("%d번째는 %d개의 원소있음\n", i, DP[i][0]);
    // }

    for (int i = 0; i <= M; i++)
    {
        if (DP[i][0] < 1)
        {
            // printf("%d번쨰에는 0개의 원소\n", i);
            continue;
        }

        DP[i][1] = 1;

        // printf("DP[%d][1] = 1", i);
        if (DP[i][0] > 1)
        {
            // printf(", DP[%d][2] = 2", i);
            DP[i][2] = 2;
        }
        // printf("\n");
    }

    // printf("\n");

    for (int i = 0; i <= M; i++)
    {
        int DPCnt = DP[i][0];

        if (DPCnt < 3)
        {
            // printf("%d번째에는 원소가 3개 이하 : %d개라서 DP 안함\n", i, DPCnt);
            continue;
        }

        for (int j = 3; j <= DPCnt; j++)
        {
            DP[i][j] = DP[i][j - 1] + DP[i][j - 2];
            // printf("DP[%d][%d] = DP[%d][%d] + DP[%d][%d] = %d\n", i, j, i, j - 1, i, j - 2, DP[i][j]);
        }
    }

    int Answer = 1;

    for (int i = 0; i <= M; i++)
    {
        if (DP[i][0] == 0)
        {
            Answer *= 1;
        }
        else
        {
            Answer *= DP[i][DP[i][0]];
        }
    }

    printf("%d", Answer);

    return 0;
}

// 입력
// 첫째 줄에는 좌석의 개수 N이 입력된다. N은 1 이상 40 이하이다. 둘째 줄에는 고정석의 개수 M이 입력된다. M은 0 이상 N 이하이다. 다음 M 개의 줄에는 고정석의 번호가 작은 수부터 큰 수의 순서로 한 줄에 하나씩 입력된다.

// 출력
// 주어진 조건을 만족하면서 사람들이 좌석에 앉을 수 있는 방법의 가짓수를 출력한다. 방법의 가짓수는 2,000,000,000을 넘지 않는다. (2,000,000,000 < 231-1)

// 예제 입력 1
// 9
// 2
// 4
// 7
// 예제 출력 1
// 12
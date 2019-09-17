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
    //     printf("%d��°�� %d���� ��������\n", i, DP[i][0]);
    // }

    for (int i = 0; i <= M; i++)
    {
        if (DP[i][0] < 1)
        {
            // printf("%d�������� 0���� ����\n", i);
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
            // printf("%d��°���� ���Ұ� 3�� ���� : %d���� DP ����\n", i, DPCnt);
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

// �Է�
// ù° �ٿ��� �¼��� ���� N�� �Էµȴ�. N�� 1 �̻� 40 �����̴�. ��° �ٿ��� �������� ���� M�� �Էµȴ�. M�� 0 �̻� N �����̴�. ���� M ���� �ٿ��� �������� ��ȣ�� ���� ������ ū ���� ������ �� �ٿ� �ϳ��� �Էµȴ�.

// ���
// �־��� ������ �����ϸ鼭 ������� �¼��� ���� �� �ִ� ����� �������� ����Ѵ�. ����� �������� 2,000,000,000�� ���� �ʴ´�. (2,000,000,000 < 231-1)

// ���� �Է� 1
// 9
// 2
// 4
// 7
// ���� ��� 1
// 12
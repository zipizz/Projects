#include <stdio.h>
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

int main(void)
{
    int N, Answer;
    int score[305], D1[305], D2[305];

    // input [ N : ����� ����, score[i] : i ��° ��ܿ� ���� ����]
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &score[i]);
    }

    // [ D1[i] i��° ��ܿ� �� ĭ�� �ö� ������ ��� ���������� �ִ� ]
    // [ D2[i] i��° ��ܿ� �� ĭ�� �ö� ������ ��� ���������� �ִ� ]
    // �ʱ�ȭ �ܰ�
    D1[0] = score[0];
    D1[1] = score[0] + score[1];

    D2[0] = score[0];
    D2[1] = score[1];

    // ���� ���α׷���.
    // i ���� ������Ű�鼭 D1[i] ���� D2[i] ���� ä�� ������.
    for (int i = 2; i < N; i++)
    {
        D1[i] = D2[i - 1] + score[i];
        D2[i] = MAX(D1[i - 2], D2[i - 2]) + score[i];
    }

    // ������ ��ܿ� �������� �� D1 �Ǵ� D2 ��Ŀ� ���� ���� ���� ��
    // ���� ���� �������� ���Ѵ�.
    Answer = MAX(D1[N - 1], D2[N - 1]);

    printf("%d", Answer);

    return 0;
}
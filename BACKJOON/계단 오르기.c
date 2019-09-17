#include <stdio.h>
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

int main(void)
{
    int N, Answer;
    int score[305], D1[305], D2[305];

    // input [ N : 계단의 갯수, score[i] : i 번째 계단에 적힌 점수]
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &score[i]);
    }

    // [ D1[i] i번째 계단에 한 칸을 올라 도달한 경우 점수총합의 최댓값 ]
    // [ D2[i] i번째 계단에 두 칸을 올라 도달한 경우 점수총합의 최댓값 ]
    // 초기화 단계
    D1[0] = score[0];
    D1[1] = score[0] + score[1];

    D2[0] = score[0];
    D2[1] = score[1];

    // 동적 프로그래밍.
    // i 값을 증가시키면서 D1[i] 값과 D2[i] 값을 채워 나간다.
    for (int i = 2; i < N; i++)
    {
        D1[i] = D2[i - 1] + score[i];
        D2[i] = MAX(D1[i - 2], D2[i - 2]) + score[i];
    }

    // 마지막 계단에 도달했을 때 D1 또는 D2 방식에 의한 점수 총합 중
    // 높은 값을 정답으로 취한다.
    Answer = MAX(D1[N - 1], D2[N - 1]);

    printf("%d", Answer);

    return 0;
}
#include <algorithm>
#include <stdio.h>

#define MAX_N 500
#define IMP -1
#define A 0
#define B 1
#define C 2

int a[MAX_N] = { 21, 14, 10, 13, 9, 0 };
int b[MAX_N] = { 23, 15, 7, 8, 1, 85 };
int c[MAX_N] = { 20, 16, 6, 10, 0, 0 };
int s[MAX_N] = { 8, 8, 20, 10, 11, 9 };
int n = 6;
int k = 2;
int DP[MAX_N][3][MAX_N];

// days �Ⱓ ����, a�Ĵ��� aDays ��ŭ �湮�� ��� ��, num Į�θ� ���밡 ������ ���̽� �� ���� ū score �� ��ȯ.
// return the max of DP[one of days][one of restaurants][aDays];
int getPossibleMax(int days, int aDays, int num)
{
    int val = IMP;

    for (int i = aDays; i <= days; i++) {
        for (int j = A; j <= C; j++) {

            // no exist
            if (DP[i][j][aDays] == IMP) {
                continue;
            }

            // impossible calories;
            if (j == A && a[i - 1] > num) {
                continue;
            }
            if (j == B && b[i - 1] > num) {
                continue;
            }
            if (j == C && c[i - 1] > num) {
                continue;
            }

            // find max score
            if (DP[i][j][aDays] > val) {
                val = DP[i][j][aDays];
            }
        }
    }
    return val;
}

int getTodayMaxScore(int beforeMaxScore, int todayScore, bool isA, int aCount)
{
    if (beforeMaxScore == IMP) {
        if (isA) {
            if (aCount == 1) {
                return todayScore;
            }
            return IMP;
        }
        if (aCount == 0) {
            return todayScore;
        }
        return IMP;
    }
    return beforeMaxScore + todayScore;
}

int main(void)
{
    for (int i = 1; i <= n; i++) {
        for (int j = A; j <= C; j++) {
            for (int l = 0; l <= n; l++) {
                DP[i][j][l] = IMP;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        DP[i][A][0] = IMP;
    }

    DP[1][B][0] = s[0];
    DP[1][C][0] = s[0];
    DP[1][A][1] = s[0];

    for (int i = 2; i <= n; i++) { // i��° ������.
        for (int j = 0; j <= i; j++) { // j : A�Ĵ翡�� ���� Ƚ��
            if (j > 0) {
                DP[i][A][j] = getTodayMaxScore(getPossibleMax(i - 1, j - 1, a[i - 1]), s[i - 1], true, j);
            }
            DP[i][B][j] = getTodayMaxScore(getPossibleMax(i - 1, j, b[i - 1]), s[i - 1], false, j);
            DP[i][C][j] = getTodayMaxScore(getPossibleMax(i - 1, j, c[i - 1]), s[i - 1], false, j);
        }
    }

    int maxScore = IMP;

    for (int i = k; i <= n; i++) {
        for (int j = A; j <= C; j++) {
            for (int l = k; l <= i; l++) {
                if (maxScore < DP[i][j][l]) {
                    maxScore = DP[i][j][l];
                }
            }
        }
    }
    printf("%d", maxScore);
    return 0;
}
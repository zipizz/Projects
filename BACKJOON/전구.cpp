#include <stdio.h>
#define INF 987654321
#define LEFT 123456
#define RIGHT 234567
#define OUT_OF_BOUNDARY 345678
int N, K;
int DP[250][250][30];
int arr[250];

int getBoundaryIdx(int left, int arrIdx, int right, int dir, int color)
{
    if (dir == LEFT) {
        while (arrIdx >= left) {
            if (arr[arrIdx] != color) {
                break;
            }
            arrIdx--;
        }
    } else if (dir == RIGHT) {
        while (arrIdx <= right) {
            if (arr[arrIdx] != color) {
                break;
            }
            arrIdx++;
        }
    }

    if (arrIdx < left || arrIdx > right) {
        return OUT_OF_BOUNDARY;
    }

    return arrIdx;
}

int getCaseCnt(int left, int mid, int right, int color)
{
    if (left == right) {
        return DP[left][left][color];
    }

    if (arr[left] == arr[right]) {
        int temp = DP[left + 1][right - 1][arr[left]];
        if (arr[left] == color) {
            return temp;
        } else {
            return temp + 1;
        }
    }

    if (left == mid) {
        if (arr[left] == arr[left + 1]) {
            return DP[left + 1][right][color];
        } else {
            return DP[left][left][color] + DP[left + 1][right][color];
        }
    }

    if (mid == right) {
        if (arr[right] == arr[right - 1]) {
            return DP[left][right - 1][color];
        } else {
            return DP[right][right][color] + DP[left][right - 1][color];
        }
    }

    if ((arr[mid - 1] != arr[mid]) && (arr[mid] != arr[mid + 1]) && (arr[mid - 1] != arr[mid + 1])) {
        return DP[left][mid - 1][color] + DP[mid][mid][color] + DP[mid + 1][right][color];
    }

    if (arr[mid - 1] != arr[mid + 1]) {
        if (arr[mid - 1] == arr[mid]) {
            return DP[left][mid][color] + DP[mid + 1][right][color];
        }
        if (arr[mid] == arr[mid + 1]) {
            return DP[left][mid - 1][color] + DP[mid][right][color];
        }
    }

    int leftSameIdx = getBoundaryIdx(left, mid, right, LEFT, arr[mid - 1]) + 1;
    int rightSameIdx = getBoundaryIdx(left, mid, right, RIGHT, arr[mid + 1]) - 1;

    if (leftSameIdx == OUT_OF_BOUNDARY + 1)
        leftSameIdx = left;
    if (rightSameIdx == OUT_OF_BOUNDARY - 1)
        rightSameIdx = right;

    int DPmerge = DP[leftSameIdx][mid - 1][color] + DP[mid + 1][rightSameIdx][color];

    if (arr[mid - 1] == arr[mid]) {
        DPmerge += DP[mid][mid][color];
    }
    if (left < leftSameIdx) {
        DPmerge += DP[left][leftSameIdx - 1][color];
    }
    if (rightSameIdx < right) {
        DPmerge += DP[rightSameIdx + 1][right][color];
    }

    return DPmerge;
}

int main(void)
{
    scanf("%d%d", &N, &K);

    for (int i = 0; i < 250; i++) {
        arr[i] = 0;
        for (int j = 0; j < 250; j++) {
            for (int k = 0; k < 30; k++) {
                DP[i][j][k] = 0;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= K; j++) {
            DP[i][i][j] = 1;
        }
        DP[i][i][arr[i]] = 0;
    }

    for (int num = 2; num <= N; num++) {
        for (int startIdx = 0; startIdx < N - num + 1; startIdx++) {
            int color = 1;
            for (; color <= K; color++) {
                int minCnt = INF;
                for (int divIdx = startIdx; divIdx < startIdx + num; divIdx++) {
                    int temp = getCaseCnt(startIdx, divIdx, startIdx + num - 1, color);
                    if (minCnt > temp) {
                        minCnt = temp;
                    }
                }

                DP[startIdx][startIdx + num - 1][color] = minCnt;
            }

            for (int i = 1; i <= K; i++) {
                for (int j = 1; j <= K; j++) {
                    if (DP[startIdx][startIdx + num - 1][i] > DP[startIdx][startIdx + num - 1][j] + 1) {
                        DP[startIdx][startIdx + num - 1][i] = DP[startIdx][startIdx + num - 1][j] + 1;
                    }
                }
            }
        }
    }

    int minAnswer = INF;

    for (int i = 1; i <= K; i++) {
        if (minAnswer > DP[0][N - 1][i])
            minAnswer = DP[0][N - 1][i];
    }

    printf("%d", minAnswer);

    return 0;
}

// #include <stdio.h>
// #define INF 987654321
// int N, K;
// int DP[205][205][25];
// int arr[205];

// int getCaseCnt(int left, int mid, int right, int color)
// {
//     if (left == right) {
//         return DP[left][left][color];
//     }

//     if (left > right) {
//         return 0;
//     }

//     if (arr[left] == arr[right]) {
//         int temp = DP[left + 1][right - 1][arr[left]];
//         if (arr[left] == color)
//             return temp;
//         else
//             return temp + 1;
//     }

//     if (left == mid) {
//         if (arr[left] == arr[left + 1])
//             return DP[left + 1][right][color];
//         else
//             return DP[left][left][color] + DP[left + 1][right][color];
//     }

//     if (mid == right) {
//         if (arr[right] == arr[right - 1])
//             return DP[left][right - 1][color];
//         else
//             return DP[right][right][color] + DP[left][right - 1][color];
//     }

//     int a, b;
//     a = DP[left][mid][color] + DP[mid + 1][right][color];
//     b = DP[left][mid - 1][color] + DP[mid][right][color];

//     return a > b ? b : a;
// }

// int main(void)
// {
//     scanf("%d%d", &N, &K);

//     for (int i = 0; i < N; i++) {
//         scanf("%d", &arr[i]);
//     }

//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < K; j++) {
//             DP[i][i][j] = 1;
//         }
//         DP[i][i][arr[i] - 1] = 0;
//     }

//     for (int num = 2; num <= N; num++) {
//         for (int startIdx = 0; startIdx < N - num + 1; startIdx++) {
//             for (int color = 0; color < K; color++) {
//                 int minCnt = INF;
//                 for (int divIdx = startIdx; divIdx < startIdx + num; divIdx++) {
//                     int temp = getCaseCnt(startIdx, divIdx, startIdx + num - 1, color);
//                     if (minCnt > temp)
//                         minCnt = temp;
//                 }
//                 DP[startIdx][startIdx + num - 1][color] = minCnt;
//             }
//         }
//     }

//     int minAnswer = INF;

//     for (int i = 0; i < K; i++) {
//         if (minAnswer > DP[0][N - 1][i])
//             minAnswer = DP[0][N - 1][i];
//     }

//     printf("%d", minAnswer);

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

int Answer;
char c[5][5];

// void DFS(int i, int j, int pathCnt, int somCnt, char pathX[], char pathY[])
// {
//     // if (i < 0 || i > 4 || j < 0 || j > 4 || pathCnt > 6 || c[i][j] == 'V')
//     // {
//     //     // printf("나가리 <%d,%d>, path : %d\n", i, j, pathCnt);
//     //     return;
//     // }

//     if (i < 0 || i > 4 || j < 0 || j > 4 || pathCnt > 6)
//     {
//         // printf("나가리 <%d,%d>, path : %d\n", i, j, pathCnt);
//         return;
//     }

//     printf("pathCnt : %d, <%d,%d>\n", pathCnt, i, j);

//     //  pathX[pathCnt] = i + '0';
//     //  pathY[pathCnt] = j + '0';

//     //  printf("들 <%d,%d>, path : %d", i, j, pathCnt);

//     if (c[i][j] == 'S')
//     {
//         somCnt++;
//         //      printf("S 증가 : %d", somCnt);
//     }

//     if (c[i][j] == 'V')
//     {
//         DFS(i + 1, j, pathCnt, somCnt, pathX, pathY);
//         DFS(i - 1, j, pathCnt, somCnt, pathX, pathY);
//         DFS(i, j + 1, pathCnt, somCnt, pathX, pathY);
//         DFS(i, j - 1, pathCnt, somCnt, pathX, pathY);
//     }
//     else
//     {
//         char tmp = c[i][j];

//         c[i][j] = 'V';

//         DFS(i + 1, j, pathCnt + 1, somCnt, pathX, pathY);
//         DFS(i - 1, j, pathCnt + 1, somCnt, pathX, pathY);
//         DFS(i, j + 1, pathCnt + 1, somCnt, pathX, pathY);
//         DFS(i, j - 1, pathCnt + 1, somCnt, pathX, pathY);

//         c[i][j] = tmp;
//     }

//     if (pathCnt < 6)
//         return;

//     if (somCnt < 4)
//     {

//         for (int i = 0; i < 7; i++)
//         {
//             //   printf("%c%c ", pathX[i], pathY[i]);
//         }
//         //  printf("som Fail\n");
//         return;
//     }

//     for (int i = 0; i < 7; i++)
//     {
//         printf("<%c,%c>->", pathX[i], pathY[i]);
//     }
//     printf("\n");

//     Answer++;
//     return;
// }

bool isAdj(int i1, int i2)
{
    int x1, x2, y1, y2;
    x1 = i1 / 5;
    y1 = i1 % 5;
    x2 = i2 / 5;
    y2 = i2 % 5;

    return (abs(x1 - x2) && abs(y1 - y2));
}

bool DFS(int aaa[])
{
    tttt[0] = 0;

    for (int i = 0; i < 7; i++)
    {
        for (int j = i + 1; j < 7; j++)
        {
            if (tttt[j] != -1)
                continue;

            if (isAdj(aaa[i], aaa[j]))
            {
                tttt[j] = i;
            }
        }
    }

    for (int i = 0; i < 7; i++)
    {
        int chkIdx = i;

        while (1)
        {
            if (tttt[chkIdx] == -1)
            {
                return false;
            }
            chkIdx = tttt[chkIdx];

            if (chkIdx == 0)
            {
                break;
            }
        }
    }

    if (!isAdj(i1, i2) &&
        !isAdj(i1, i3) &&
        !isAdj(i1, i4) &&
        !isAdj(i1, i5) &&
        !isAdj(i1, i6) &&
        !isAdj(i1, i7))
        return false;
    if (isAdj(i1, i2))
    {
        tttt[1] = 1;
    }

    if (!isAdj(i2, i3) &&
        !isAdj(i2, i4) &&
        !isAdj(i2, i5) &&
        !isAdj(i2, i6) &&
        !isAdj(i2, i7))
        return false;

    if (!isAdj(i3, i4) &&
        !isAdj(i3, i5) &&
        !isAdj(i3, i6) &&
        !isAdj(i3, i7))
        return false;

    if (!isAdj(i4, i5) &&
        !isAdj(i4, i6) &&
        !isAdj(i4, i7))
        return false;

    if (!isAdj(i5, i6) &&
        !isAdj(i5, i7))
        return false;

    if (!isAdj(i6, i7))
        return false;

    return true;
}

int main(void)
{
    char a[5][5];
    int tttt[7];

    for (int i = 0; i < 7; i++)
    {
        tttt[i] = -1;
    }
    for (int i = 0; i < 5; i++)
    {
        scanf("%s", &a[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            c[i][j] = a[i][j];
        }
    }

    // int somCnt = 0;

    // for (int i = 0; i < 5; i++)
    // {
    //     for (int j = 0; j < 5; j++)
    //     {
    //         char pathX[7];
    //         char pathY[7];
    //         DFS(i, j, 0, 0, pathX, pathY);
    //     }
    // }

    for (int i1 = 0; i1 < 19; i1++)
    {
        int somCnt = 0;
        if (c[i1 / 5][i1 % 5] == 'S')
            somCnt++;
        for (int i2 = i1 + 1; i2 < 20; i2++)
        {
            if (c[i2 / 5][i2 % 5] == 'S')
                somCnt++;
            for (int i3 = i2 + 1; i3 < 21; i3++)
            {
                if (c[i3 / 5][i3 % 5] == 'S')
                    somCnt++;
                for (int i4 = i3 + 1; i4 < 22; i4++)
                {
                    if (c[i4 / 5][i4 % 5] == 'S')
                        somCnt++;

                    if (somCnt <= 0)
                        continue;

                    for (int i5 = i4 + 1; i5 < 23; i5++)
                    {
                        if (c[i5 / 5][i5 % 5] == 'S')
                            somCnt++;

                        if (somCnt <= 1)
                            continue;

                        for (int i6 = i5 + 1; i6 < 24; i6++)
                        {
                            if (c[i6 / 5][i6 % 5] == 'S')
                                somCnt++;

                            if (somCnt <= 2)
                                continue;

                            for (int i7 = i6 + 1; i7 < 25; i7++)
                            {
                                if (c[i7 / 5][i7 % 5] == 'S')
                                    somCnt++;

                                if (somCnt <= 3)
                                    continue;
                                int aaa[7];

                                aaa[0] = i1;
                                aaa[1] = i2;
                                aaa[2] = i3;
                                aaa[3] = i4;
                                aaa[4] = i5;
                                aaa[5] = i6;
                                aaa[6] = i7;

                                if (DFS(aaa))
                                    Answer++;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d", Answer);

    return 0;
}

// 입력
// 'S'(이다‘솜’파의 학생을 나타냄) 또는 'Y'(임도‘연’파의 학생을 나타냄)을 값으로 갖는 5*5 행렬이 공백 없이 첫째 줄부터 다섯 줄에 걸쳐 주어진다.

// 출력
// 첫째 줄에 ‘소문난 칠공주’를 결성할 수 있는 모든 경우의 수를 출력한다.

// 예제 입력 1
// YYYYY
// SYSYS
// YYYYY
// YSYYS
// YYYYY
// 예제 출력 1
// 2
// 출처
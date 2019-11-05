#include <algorithm>
#include <stdio.h>
#include <string>

using namespace std;

int score[26][26];
int n, m, Xn, Yn;
char x[1000], y[1000];

void setScore(char a, char b, int num)
{
    score[a - 'a'][b - 'a'] = num;
}

int main(void)
{
    int DP[500][500][2];

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            score[i][j] = 0;
        }
    }

    printf("input N : ");
    scanf("%d", &n);
    printf("input m(Xn) : ");
    scanf("%d", &m);
    Xn = m;
    Yn = n - Xn;
    printf("input String(X) : ");
    scanf("%s", x);
    printf("input String(Y) : ");
    scanf("%s", y);

    // do = 100, dr = 80, ds = 20, od = 60, or = 100,
    // os = 60, ow = 40, rd = 70, rs = 15, rw = 7, so = 65,
    // sr = 3, wd = 1, wo = 50, wr = 70
    setScore('d', 'o', 100);
    setScore('d', 'r', 80);
    setScore('d', 's', 20);
    setScore('o', 'd', 60);
    setScore('o', 'r', 100);

    setScore('o', 's', 60);
    setScore('o', 'w', 40);
    setScore('r', 'd', 70);
    setScore('r', 's', 15);
    setScore('r', 'w', 7);
    setScore('s', 'o', 65);

    setScore('s', 'r', 3);
    setScore('w', 'd', 1);
    setScore('w', 'o', 50);
    setScore('w', 'r', 70);

    printf("n : %d, Xn(m) : %d, Yn : %d, x : %s, y : %s\n", n, Xn, Yn, x, y);

    for (int i = 0; i <= Xn; i++) {
        for (int j = 0; j <= Yn; j++) {
            DP[i][j][0] = 0;
            DP[i][j][1] = 0;
        }
    }
    // words
    // wds , or
    for (int i = 2; i <= Xn; i++) {
        DP[i][0][0] = DP[i - 1][0][0] + score[x[Xn - i] - 'a'][x[Xn - i + 1] - 'a'];
        DP[i][1][1] = score[y[Yn - 1] - 'a'][x[Xn - i] - 'a'] + DP[i][0][0];
    }

    for (int i = 2; i <= Yn; i++) {
        DP[0][i][1] = DP[0][i - 1][1] + score[y[Yn - i] - 'a'][y[Yn - i + 1] - 'a'];
        DP[1][i][0] = score[x[Xn - 1] - 'a'][y[Yn - i] - 'a'] + DP[0][i][1];
    }

    DP[1][1][0] = score[x[Xn - 1] - 'a'][y[Yn - 1] - 'a'];
    DP[1][1][1] = score[y[Yn - 1] - 'a'][x[Xn - 1] - 'a'];

    for (int i = 1; i <= Xn; i++) {
        for (int j = 1; j <= Yn; j++) {
            if (i == 1 && j == 1)
                continue;

            if (i >= 2) {
                DP[i][j][0] = max(DP[i - 1][j][0] + score[x[Xn - i] - 'a'][x[Xn - i + 1] - 'a'], DP[i - 1][j][1] + score[x[Xn - i] - 'a'][y[Yn - j] - 'a']);
            }
            if (j >= 2) {
                DP[i][j][1] = max(DP[i][j - 1][0] + score[y[Yn - j] - 'a'][x[Xn - i] - 'a'], DP[i][j - 1][1] + score[y[Yn - j] - 'a'][y[Yn - j + 1] - 'a']);
            }
        }
    }

    printf("Answer : %d\n", max(DP[Xn][Yn][0], DP[Xn][Yn][1]));

    return 0;
}
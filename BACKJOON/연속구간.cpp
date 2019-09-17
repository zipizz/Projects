#include <iostream>

using namespace std;

int main(void)
{
    int a[3];
    int seq[3][8];

    cin >> a[0] >> a[1] >> a[2];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            seq[i][j] = a[i] % 10;
            a[i] /= 10;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        int howLong = 1;
        int longest = 1;

        for (int j = 1; j < 8; j++)
        {
            if (seq[i][j] == seq[i][j - 1])
            {
                howLong++;
                if (longest < howLong)
                {
                    longest = howLong;
                }
            }
            else
            {
                howLong = 1;
            }
        }
        cout << longest << endl;
    }

    return 0;
}

// 첫째 줄에서 셋째 줄까지 한 줄에 하나씩 각 입력된  수 내에서 같은 숫자가 연속하여 나오는 가장 긴 길이를 입력 순서대로 출력한다.

// 예제 입력 1
// 12345123
// 17772345
// 22233331
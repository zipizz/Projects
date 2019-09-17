#include <iostream>

using namespace std;

int main(void)
{
    int N;
    int seq[100005];
    int longest = 1;
    int inc = 1;
    int dec = 1;

    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> seq[i];
    }

    for (int i = 1; i < N; i++)
    {
        if (seq[i - 1] < seq[i])
        {
            inc++;
            dec = 1;
            if (longest < inc)
            {
                longest = inc;
            }
        }
        else if (seq[i - 1] == seq[i])
        {
            inc++;
            dec++;
            if (longest < inc)
            {
                longest = inc;
            }
            if (longest < dec)
            {
                longest = dec;
            }
        }
        else
        {
            dec++;
            inc = 1;
            if (longest < dec)
            {
                longest = dec;
            }
        }
    }

    cout << longest;

    return 0;
}

// 첫째 줄에는 수열의 길이 N이 주어지고, 둘째 줄에는 N개의 숫자가 빈칸을 사이에 두고 주어진다. N은 1 이상 100,000 이하의 정수이다.

// 출력
// 첫째 줄에 가장 긴 길이를 출력한다.

// 예제 입력 1
// 9
// 1 2 2 4 4 5 7 7 2
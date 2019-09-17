#include <iostream>

using namespace std;

int main(void)
{
    int N, partN;
    int seq[100000];
    int partSum[100000] = {0};
    bool sign;

    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> seq[i];
    }

    if (seq[0] >= 0)
        sign = true;
    else
        sign = false;

    partSum[0] = seq[0];
    partN = 1;

    for (int i = 1, j = 0; i < N; i++)
    {
        if ((sign && (seq[i] >= 0)) || (!sign && (seq[i] < 0))) // 부호가 유지됨.
        {
            partSum[j] += seq[i];
        }
        else // 부호가 반전됨.
        {
            sign = !sign;
            partSum[++j] += seq[i];
            partN = j + 1;
        }
    }

    if (partN == 1 && partSum[0] < 0)
    {
        int partMax = seq[0];
        for (int i = 0; i < N; i++)
        {
            if (partMax < seq[i])
            {
                partMax = seq[i];
            }
        }
        cout << partMax;
        return 0;
    }

    int sum = 0;
    int max = 0;

    for (int i = 0; i < partN; i++)
    {
        if (partSum[i] >= 0)
        {
            sum += partSum[i];
            if (max < sum)
            {
                max = sum;
            }
        }
        else
        {
            sum += partSum[i];
            if (sum < 0)
            {
                sum = 0;
            }
        }
    }

    cout << max;
    return 0;
}

// // 첫째 줄에 정수 n(1 ≤ n ≤ 100,000)이 주어지고 둘째 줄에는 n개의 정수로 이루어진 수열이 주어진다. 수는 -1,000보다 크거나 같고, 1,000보다 작거나 같은 정수이다.

// // 출력
// // 첫째 줄에 답을 출력한다.

// // 예제 입력 1
// // 10
// // 10 -4 3 1 5 6 -35 12 21 -1
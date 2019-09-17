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
        if ((sign && (seq[i] >= 0)) || (!sign && (seq[i] < 0))) // ��ȣ�� ������.
        {
            partSum[j] += seq[i];
        }
        else // ��ȣ�� ������.
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

// // ù° �ٿ� ���� n(1 �� n �� 100,000)�� �־����� ��° �ٿ��� n���� ������ �̷���� ������ �־�����. ���� -1,000���� ũ�ų� ����, 1,000���� �۰ų� ���� �����̴�.

// // ���
// // ù° �ٿ� ���� ����Ѵ�.

// // ���� �Է� 1
// // 10
// // 10 -4 3 1 5 6 -35 12 21 -1
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

// ù° �ٿ��� ������ ���� N�� �־�����, ��° �ٿ��� N���� ���ڰ� ��ĭ�� ���̿� �ΰ� �־�����. N�� 1 �̻� 100,000 ������ �����̴�.

// ���
// ù° �ٿ� ���� �� ���̸� ����Ѵ�.

// ���� �Է� 1
// 9
// 1 2 2 4 4 5 7 7 2
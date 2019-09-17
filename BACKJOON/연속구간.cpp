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

// ù° �ٿ��� ��° �ٱ��� �� �ٿ� �ϳ��� �� �Էµ�  �� ������ ���� ���ڰ� �����Ͽ� ������ ���� �� ���̸� �Է� ������� ����Ѵ�.

// ���� �Է� 1
// 12345123
// 17772345
// 22233331
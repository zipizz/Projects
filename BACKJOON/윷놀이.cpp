#include <iostream>

using namespace std;

int main(void)
{
    char Answer[3];

    for (int i = 0, sum; i < 3; i++)
    {
        for (int j = sum = 0, temp; j < 4; j++)
        {
            cin >> temp;
            sum += temp;
        }
        switch (sum)
        {
        case 0:
            Answer[i] = 'D';
            break;
        case 1:
            Answer[i] = 'C';
            break;
        case 2:
            Answer[i] = 'B';
            break;
        case 3:
            Answer[i] = 'A';
            break;
        case 4:
            Answer[i] = 'E';
            break;
        }
    }

    cout << Answer[0] << endl;
    cout << Answer[1] << endl;
    cout << Answer[2] << endl;

    return 0;
}

// �Է�
// ù° �ٺ��� ��° �ٱ��� �� �ٿ� ���� �� �� ���� ��¦���� ���¸� ��Ÿ���� �� ���� ����(0 �Ǵ� 1)��  ��ĭ�� ���̿� �ΰ� �־�����.

// ���
// ù° �ٺ��� ��° �ٱ��� �� �ٿ� �ϳ��� �����  ���� A, ���� B, ���� C, ���� D, ��� E�� ����Ѵ�.

// ���� �Է� 1
// 0 1 0 1
// 1 1 1 0
// 0 0 1 1
// 0 1 0 1
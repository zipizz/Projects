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

// 입력
// 첫째 줄부터 셋째 줄까지 각 줄에 각각 한 번 던진 윷짝들의 상태를 나타내는 네 개의 정수(0 또는 1)가  빈칸을 사이에 두고 주어진다.

// 출력
// 첫째 줄부터 셋째 줄까지 한 줄에 하나씩 결과를  도는 A, 개는 B, 걸은 C, 윷은 D, 모는 E로 출력한다.

// 예제 입력 1
// 0 1 0 1
// 1 1 1 0
// 0 0 1 1
// 0 1 0 1
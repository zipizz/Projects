#include <stdio.h>

int main(void)
{
    int Answer = 0;
    bool isChar = false;
    char c;

    while (1)
    {
        scanf("%c", &c);

        if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        {
            break;
        }

        if (c == ' ')
        {
            isChar = false;
        }
        else
        {
            if (!isChar)
                Answer++;
            isChar = true;
        }
    }

    printf("%d", Answer);

    return 0;
}

// 입력
// 첫 줄에 영어 대소문자와 띄어쓰기로 이루어진 문자열이 주어진다. 이 문자열의 길이는 1,000,000을 넘지 않는다. 단어는 띄어쓰기 한 개로 구분되며, 공백이 연속해서 나오는 경우는 없다. 또한 문자열의 앞과 뒤에는 공백이 있을 수도 있다.

// 출력
// 첫째 줄에 단어의 개수를 출력한다.

// 예제 입력 1
// The Curious Case of Benjamin Button
// 예제 출력 1
// 6
// 예제 입력 2
//  Mazatneunde Wae Teullyeoyo
// 예제 출력 2
// 3
// 예제 입력 3
// Teullinika Teullyeotzi
// 예제 출력 3
// 2
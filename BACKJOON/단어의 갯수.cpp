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

// �Է�
// ù �ٿ� ���� ��ҹ��ڿ� ����� �̷���� ���ڿ��� �־�����. �� ���ڿ��� ���̴� 1,000,000�� ���� �ʴ´�. �ܾ�� ���� �� ���� ���еǸ�, ������ �����ؼ� ������ ���� ����. ���� ���ڿ��� �հ� �ڿ��� ������ ���� ���� �ִ�.

// ���
// ù° �ٿ� �ܾ��� ������ ����Ѵ�.

// ���� �Է� 1
// The Curious Case of Benjamin Button
// ���� ��� 1
// 6
// ���� �Է� 2
//  Mazatneunde Wae Teullyeoyo
// ���� ��� 2
// 3
// ���� �Է� 3
// Teullinika Teullyeotzi
// ���� ��� 3
// 2
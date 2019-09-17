#include <stdio.h>

int h[200050];

void heapInsert(int n)
{
    h[0]++;

    int child = h[0];
    int parent = child / 2;

    while (parent)
    {
        if (n > h[parent])
            h[child] = h[parent];
        else
        {
            break;
        }

        child = parent;
        parent /= 2;
    }

    h[child] = n;
}

int heapDelete()
{
    if (!h[0])
    {
        return 0;
    }

    int max = h[1];
    h[1] = h[h[0]];
    h[h[0]] = 0;
    h[0]--;

    int n = h[1];
    int parent = 1;
    int child = parent * 2;

    while (parent <= h[0])
    {
        if ((child + 1 <= h[0]) && h[child] < h[child + 1])
        {
            child++;
        }

        if (n < h[child])
        {
            h[parent] = h[child];
        }
        else
        {
            break;
        }

        parent = child;
        child *= 2;
    }

    h[parent] = n;

    return max;
}

int main(void)
{
    int N, x;
    int printCount = 0;
    scanf("%d", &N);
    h[0] = 0;

    int Answer[200050];

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &x);

        if (x)
        {
            heapInsert(x);
        }
        else
        {
            Answer[printCount++] = heapDelete();
        }
    }

    for (int i = 0; i < printCount; i++)
    {
        printf("%d\n", Answer[i]);
    }

    return 0;
}
// �Է�
// ù° �ٿ� ������ ���� N(1��N��100,000)�� �־�����. ���� N���� �ٿ��� ���꿡 ���� ������ ��Ÿ���� ���� x�� �־�����. ���� x�� �ڿ������ �迭�� x��� ���� �ִ�(�߰��ϴ�) �����̰�, x�� 0�̶�� �迭���� ���� ū ���� ����ϰ� �� ���� �迭���� �����ϴ� ����̴�. �ԷµǴ� �ڿ����� 2^31���� �۴�.

// ���
// �Է¿��� 0�� �־��� ȸ����ŭ ���� ����Ѵ�. ���� �迭�� ��� �ִ� ����ε� ���� ū ���� ����϶�� �� ��쿡�� 0�� ����ϸ� �ȴ�.

// ���� �Է� 1
// 13
// 0
// 1
// 2
// 0
// 0
// 3
// 2
// 1
// 0
// 0
// 0
// 0
// 0
// ���� ��� 1
// 0
// 2
// 1
// 3
// 2
// 1
// 0
// 0
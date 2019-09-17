#include <stdio.h>

int arr[500050];
int Answer[500050];

int binarySearchIndex(int left, int right, int x)
{
    int mid = (left + right) / 2;

    if (arr[mid] < x)
    {
        if (mid == right)
        {
            return mid + 1;
        }

        if (x < arr[mid + 1])
        {
            return mid + 1;
        }

        return binarySearchIndex(mid + 1, right, x);
    }

    if (mid == 0)
    {
        return 0;
    }

    if (arr[mid - 1] < x)
    {
        return mid;
    }

    return binarySearchIndex(left, mid - 1, x);
}

void binaryInsert(int x, int n)
{
    int sortedIdx = binarySearchIndex(0, n - 1, x);

    for (int i = n; i > sortedIdx; i--)
    {
        arr[i] = arr[i - 1];
    }

    arr[sortedIdx] = x;
    Answer[n] = n - sortedIdx + 1;
}

int main(void)
{
    int N;

    scanf("%d", &N);
    scanf("%d", &arr[0]);
    Answer[0] = 1;

    for (int i = 1; i < N; i++)
    {
        scanf("%d", &arr[i]);
        binaryInsert(arr[i], i);
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d\n", Answer[i]);
    }

    return 0;
}

// ù° �ٿ��� ������ ���� �ǹ��ϴ� ���� N�� �־�����. N�� 3 �̻� 500,000 �����̴�. ���� N���� �ٿ��� ������ �� �ٿ� �ϳ��� �־�����. �� ������ �� �������� ��� �Ƿ��� �տ��� �޸��� �ִ� �������� ������ ���̴�. �� ������ 1 �̻� 1,000,000,000 �����̴�. ��, ������ �������� ��� �Ƿ��� ��� �ٸ���.

// ���
// �� ������ �ּ��� ����� ��Ÿ���� ���� N���� �Է¿� �־��� ���� ������ ������ ������ �� �ٿ� �ϳ��� ����Ѵ�.

// ���� �Է� 1
// 8
// 2
// 8
// 10
// 7
// 1
// 9
// 4
// 15
// ���� ��� 1
// 1
// 1
// 1
// 3
// 5
// 2
// 5
// 1
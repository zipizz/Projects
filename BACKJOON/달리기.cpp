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

// 첫째 줄에는 선수의 수를 의미하는 정수 N이 주어진다. N은 3 이상 500,000 이하이다. 이후 N개의 줄에는 정수가 한 줄에 하나씩 주어진다. 이 값들은 각 선수들의 평소 실력을 앞에서 달리고 있는 선수부터 제시한 것이다. 각 정수는 1 이상 1,000,000,000 이하이다. 단, 참가한 선수들의 평소 실력은 모두 다르다.

// 출력
// 각 선수의 최선의 등수를 나타내는 정수 N개를 입력에 주어진 선수 순서와 동일한 순서로 한 줄에 하나씩 출력한다.

// 예제 입력 1
// 8
// 2
// 8
// 10
// 7
// 1
// 9
// 4
// 15
// 예제 출력 1
// 1
// 1
// 1
// 3
// 5
// 2
// 5
// 1
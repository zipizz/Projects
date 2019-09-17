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
// 입력
// 첫째 줄에 연산의 개수 N(1≤N≤100,000)이 주어진다. 다음 N개의 줄에는 연산에 대한 정보를 나타내는 정수 x가 주어진다. 만약 x가 자연수라면 배열에 x라는 값을 넣는(추가하는) 연산이고, x가 0이라면 배열에서 가장 큰 값을 출력하고 그 값을 배열에서 제거하는 경우이다. 입력되는 자연수는 2^31보다 작다.

// 출력
// 입력에서 0이 주어진 회수만큼 답을 출력한다. 만약 배열이 비어 있는 경우인데 가장 큰 값을 출력하라고 한 경우에는 0을 출력하면 된다.

// 예제 입력 1
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
// 예제 출력 1
// 0
// 2
// 1
// 3
// 2
// 1
// 0
// 0
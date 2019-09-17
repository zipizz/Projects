#include <stdio.h>
#include <stdlib.h>

int priNumCnt;
int primeGraph[1100][1100];
int priNumArr[1100];
bool isPriNum[10000];

int root(int n)
{
    if (n < 1)
        return 0;

    int i = 1;

    while (1)
    {
        if (i * i > n)
        {
            return i - 1;
        }

        i++;
    }
}

bool isPriNumFunc(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i <= root(n); i++)
    {
        if ((n % i) == 0)
        {
            return false;
        }
    }

    return true;
}

void setPriNum()
{
    int smallPriNumArr[100];
    int priNumCount = 0;
    priNumCnt = 0;

    for (int i = 2; i < 100; i++)
    {
        if (isPriNumFunc(i))
        {
            smallPriNumArr[priNumCount++] = i;
        }
    }

    for (int i = 0; i < priNumCount; i++)
    {
        int priNum = smallPriNumArr[i];
        for (int j = 2; j * priNum < 10000; j++)
        {
            isPriNum[j * priNum] = false;
        }
    }

    isPriNum[0] = false;
    isPriNum[1] = false;

    for (int i = 1000; i < 10000; i++)
    {
        if (isPriNum[i])
        {
            priNumArr[priNumCnt++] = i;
        }
    }
}

bool isOneDiff(int a, int b)
{
    int count = 0;

    for (int i = 0; i < 4; i++, a /= 10, b /= 10)
    {
        if ((a % 10) != (b % 10))
            count++;
    }

    if (count == 1)
        return true;

    return false;
}

struct node
{
    int data;
    int path = 0;
};

struct Queue
{
    int size = 1100;
    int front = 0;
    int rear = 0;
    node arr[1100];
};

Queue Q;

bool isFullQ()
{
    if (((Q.front) % (Q.size)) == ((Q.rear + 1) % (Q.size)))
        return true;

    return false;
}

bool isEmptyQ()
{
    if ((Q.front) % (Q.size) == ((Q.rear) % (Q.size)))
        return true;

    return false;
}

void enqueue(int num, int pathCnt)
{
    if (isFullQ())
    {
        return;
    }

    Q.arr[Q.rear].data = num;
    Q.arr[Q.rear].path = pathCnt;

    Q.rear++;
    Q.rear = Q.rear % Q.size;
}

node dequeue()
{
    if (isEmptyQ())
    {
        node temp;
        temp.data = -1;
        return temp;
    }

    node x;
    x.data = Q.arr[Q.front].data;
    x.path = Q.arr[Q.front].path;
    Q.front++;
    Q.front = Q.front % Q.size;

    return x;
}

bool check[1100];
int Answer[10000];

void BFS(int output, int pathCnt, int answerIdx)
{
    while (1)
    {
        node x = dequeue();
        int inIdx = x.data;
        pathCnt = x.path;

        if (inIdx == -1)
        {
            Answer[answerIdx] = 0;
            return;
        }

        for (int i = 0; i < priNumCnt; i++)
        {
            if (!primeGraph[inIdx][i])
                continue;

            if (priNumArr[i] == output)
            {
                if (Answer[answerIdx] > pathCnt + 1)
                {
                    Answer[answerIdx] = pathCnt + 1;
                }
                return;
            }

            if (!check[i])
            {
                enqueue(i, pathCnt + 1);
                check[i] = true;
            }
        }
    }
}

void initQ()
{
    Q.size = 1100;
    Q.front = 0;
    Q.rear = 0;
    for (int i = 0; i < 1100; i++)
    {
        Q.arr[i].data = 0;
        Q.arr[i].path = 0;
    }
}

int main(void)
{
    int N;

    for (int i = 0; i < 10000; i++)
    {
        isPriNum[i] = true;
    }

    scanf("%d", &N);
    setPriNum();

    for (int i = 0; i < priNumCnt; i++)
    {
        int priNum = priNumArr[i];

        for (int j = 0; j < priNumCnt; j++)
        {
            if (isOneDiff(priNum, priNumArr[j]))
            {
                primeGraph[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        Answer[i] = 10000;

        int input, output;

        scanf("%d %d", &input, &output);

        if (input == output)
        {
            Answer[i] = 0;
            continue;
        }

        for (int j = 0; j < priNumCnt; j++)
        {
            if (input == priNumArr[j])
            {
                enqueue(j, 0);
                check[j] = true;
                break;
            }
        }

        BFS(output, 0, i);

        initQ();

        for (int j = 0; j < 1100; j++)
        {
            check[j] = false;
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d\n", Answer[i]);
    }

    return 0;
}
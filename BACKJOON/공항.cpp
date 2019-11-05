#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INSERT_FAIL_FLAG -1

struct segmentNode {
    int min;
    int max;
    bool isFull;
} T[600150];

int height = 0;
int leafIdx = 1;

void DFS(int idx)
{
    if (idx >= leafIdx) {
        T[idx].min = idx - leafIdx + 1;
        T[idx].max = idx - leafIdx + 1;
        T[idx].isFull = false;
        return;
    }

    DFS(idx * 2);
    DFS(idx * 2 + 1);
    T[idx].min = T[idx * 2].min;
    T[idx].max = T[idx * 2 + 1].max;
    T[idx].isFull = false;
}

int insert(int idx, int num)
{
    if (!T[leafIdx + num - 1].isFull) {
        T[leafIdx + num - 1].isFull = true;
        return leafIdx + num - 1;
    }

    if (idx >= leafIdx) {
        if (!T[idx].isFull) {
            T[idx].isFull = true;
            return idx;
        }
        return INSERT_FAIL_FLAG;
    }

    if (T[idx].isFull) {
        return INSERT_FAIL_FLAG;
    }

    if (T[idx].min > num) {
        return INSERT_FAIL_FLAG;
    }

    int insertIdx = insert(idx * 2 + 1, num);
    if (insertIdx == INSERT_FAIL_FLAG) {
        insertIdx = insert(idx * 2, num);
    }
    return insertIdx;
}

void update(int idx, int num)
{
    while (idx) {
        if (T[idx].min == num) {
            T[idx].min++;
        }
        if (T[idx].max == num) {
            T[idx].max--;
        }
        if (T[idx].min > T[idx].max) {
            T[idx].isFull = true;
        }
        idx /= 2;
    }
}

int main(void)
{
    printf("asdf");
    int gateN, planeN;
    int gi[300050];
    printf("asdf");
    int Answer = 0;

    srand(time(NULL));

    clock_t start, end;
    double result;

    scanf("%d%d", &gateN, &planeN);
    // gateN = planeN = 100000;
    for (int i = 0; i < planeN; i++) {
        scanf("%d", &gi[i]);
        // gi[i] = (rand() % 100000) + 1;
    }
    start = clock();
    int tempGateN = gateN;

    while (tempGateN) {
        tempGateN /= 2;
        height++;
        leafIdx *= 2;
    }
    leafIdx /= 2;

    DFS(1);

    for (int i = 0; i < planeN; i++) {
        int insertedIdx = insert(1, gi[i]);
        if (insertedIdx != INSERT_FAIL_FLAG) {
            Answer++;
            update(insertedIdx, gi[i]);
        } else {
            break;
        }
    }

    printf("%d", Answer);

    end = clock(); //시간 측정 끝
    result = (double)(end - start);
    printf("\n%f", result);

    return 0;
}
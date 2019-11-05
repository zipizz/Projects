#include <cstdlib>
#include <stdio.h>
#define NORTH 1
#define SOUTH 2
#define WEST 3
#define EAST 4
#define MIN(a, b) a > b ? b : a

int oppositeMax(int dis1, int dis2, int entireDis, int defaultDis)
{
    int a = dis1 + dis2;
    int b = entireDis - dis1 + entireDis - dis2;
    if (a > b) {
        printf("a: %d,entireDis : %d, b:%d, default : %d\n", a, entireDis, b, defaultDis);
    }
    return ((MIN(a, b)) + defaultDis);
}

int main(void)
{
    int N;
    int xSize, ySize;
    int direction[105];
    int distance[105];
    int pointDir, pointDis;
    int Answer = 0;

    scanf("%d%d%d", &xSize, &ySize, &N);

    for (int i = 0; i < N; i++) {
        scanf("%d%d", &direction[i], &distance[i]);
    }
    scanf("%d%d", &pointDir, &pointDis);

    // 1 ��
    // 2 ��
    // 3 ��
    // 4 ��

    // �ð� ����31 �ϵ�14 ����42 ����23
    // �ݽð� �ϼ�13 ����32 ����24 ����41
    // ��� �ϳ� ���� ���� ����
    // �Ϻ� ���� ���� ���� (���̸� ��ȯ)
    for (int i = 0; i < N; i++) {
        switch (pointDir) {
        case NORTH:
            switch (direction[i]) {
            case NORTH:
                Answer += abs(pointDis - distance[i]);
                break;
            case SOUTH:
                Answer += oppositeMax(pointDis, distance[i], xSize, ySize);
                break;
            case WEST:
                Answer += (pointDis + distance[i]);
                break;
            case EAST:
                Answer += (xSize - pointDis + distance[i]);
                break;
            default:
                break;
            }
            break;
        case SOUTH:
            switch (direction[i]) {
            case NORTH:
                printf("Answer : %d\n", Answer);
                printf("temp : %d\n", oppositeMax(pointDis, distance[i], xSize, ySize));
                Answer += oppositeMax(pointDis, distance[i], xSize, ySize);
                printf("Answer : %d\n", Answer);
                break;
            case SOUTH:
                Answer += abs(pointDis - distance[i]);
                break;
            case WEST:
                Answer += (pointDis + ySize - distance[i]);
                break;
            case EAST:
                Answer += (xSize - pointDis + ySize - distance[i]);
                break;
            default:
                break;
            }
            break;
        case WEST:
            switch (direction[i]) {
            case NORTH:
                Answer += (pointDis + distance[i]);
                break;
            case SOUTH:
                Answer += (ySize - pointDis + distance[i]);
                break;
            case WEST:
                Answer += abs(pointDis - distance[i]);
                break;
            case EAST:
                Answer += oppositeMax(pointDis, distance[i], ySize, xSize);
                break;
            default:
                break;
            }
            break;
        case EAST:
            switch (direction[i]) {
            case NORTH:
                Answer += (pointDis + xSize - distance[i]);
                break;
            case SOUTH:
                Answer += (ySize - pointDis + xSize - distance[i]);
                break;
            case WEST:
                Answer += oppositeMax(pointDis, distance[i], ySize, xSize);
                break;
            case EAST:
                Answer += abs(pointDis - distance[i]);
                break;
            default:
                break;
            }
            break;
        }
    }

    printf("%d", Answer);
    return 0;
}
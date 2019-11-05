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

    // 1 ºÏ
    // 2 ³²
    // 3 ¼­
    // 4 µ¿

    // ½Ã°è ¼­ºÏ31 ºÏµ¿14 µ¿³²42 ³²¼­23
    // ¹Ý½Ã°è ºÏ¼­13 ¼­³²32 ³²µ¿24 µ¿ºÏ41
    // °í·Á ºÏ³² ³²ºÏ ¼­µ¿ µ¿¼­
    // ºÏºÏ ³²³² ¼­¼­ µ¿µ¿ (Â÷ÀÌ¸¦ ¹ÝÈ¯)
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
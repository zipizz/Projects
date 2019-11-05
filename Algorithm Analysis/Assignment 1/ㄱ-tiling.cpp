// k, 좌표 값 입력 받음.
#include <math.h>
#include <stdio.h>

void DFS(int startX, int startY, int targetX, int targetY, int k)
{
    if (k == 1) {
        if (startX == targetX) {
            if (startY == targetY) { // target is left-top of mass
                printf("{(%d,%d), (%d,%d), (%d,%d)}\n",
                    startY, startX + 1, startY + 1, startX + 1, startY + 1, startX);
            } else { // target is left-bottom of mass
                printf("{(%d,%d), (%d,%d), (%d,%d)}\n",
                    startY, startX, startY, startX + 1, startY + 1, startX + 1);
            }
        } else {
            if (startY == targetY) { // target is right-top of mass
                printf("{(%d,%d), (%d,%d), (%d,%d)}\n",
                    startY, startX, startY + 1, startX, startY + 1, startX + 1);
            } else { // target is right-bottom of mass
                printf("{(%d,%d), (%d,%d), (%d,%d)}\n",
                    startY, startX + 1, startY, startX, startY + 1, startX);
            }
        }
        return;
    }

    int distance = pow(2, k - 1);
    if (targetX < startX + distance) { // left
        if (targetY < startY + distance) { // left top
            printf("{(%d,%d), (%d,%d), (%d,%d)}\n", startY + distance - 1, startX + distance,
                startY + distance, startX + distance, startY + distance, startX + distance - 1);
            DFS(startX, startY, targetX, targetY, k - 1); // left top
            DFS(startX + distance, startY, startX + distance, startY + distance - 1, k - 1); // right top
            DFS(startX + distance, startY + distance, startX + distance, startY + distance, k - 1); // right bottom
            DFS(startX, startY + distance, startX + distance - 1, startY + distance, k - 1); // left bottom
        } else { // left bottom
            printf("{(%d,%d), (%d,%d), (%d,%d)}\n", startY + distance - 1, startX + distance - 1,
                startY + distance - 1, startX + distance, startY + distance, startX + distance);
            DFS(startX, startY + distance, targetX, targetY, k - 1); // left bottom
            DFS(startX, startY, startX + distance - 1, startY + distance - 1, k - 1); // left top
            DFS(startX + distance, startY, startX + distance, startY + distance - 1, k - 1); // right top
            DFS(startX + distance, startY + distance, startX + distance, startY + distance, k - 1); // right bottom
        }
    } else { // right
        if (targetY < startY + distance) { // right top
            printf("{(%d,%d), (%d,%d), (%d,%d)}\n", startY + distance - 1, startX + distance - 1,
                startY + distance, startX + distance - 1, startY + distance, startX + distance);
            DFS(startX + distance, startY, targetX, targetY, k - 1); // right top
            DFS(startX, startY, startX + distance - 1, startY + distance - 1, k - 1); // left top
            DFS(startX, startY + distance, startX + distance - 1, startY + distance, k - 1); // left bottom
            DFS(startX + distance, startY + distance, startX + distance, startY + distance, k - 1); // right bottom
        } else { // right bottom
            printf("{(%d,%d), (%d,%d), (%d,%d)}\n", startY + distance - 1, startX + distance,
                startY + distance - 1, startX + distance - 1, startY + distance, startX + distance - 1);
            DFS(startX + distance, startY + distance, targetX, targetY, k - 1); // right bottom
            DFS(startX + distance, startY, startX + distance, startY + distance - 1, k - 1); // right top
            DFS(startX, startY, startX + distance - 1, startY + distance - 1, k - 1); // left top
            DFS(startX, startY + distance, startX + distance - 1, startY + distance, k - 1); // left bottom
        }
    }
}
int main(void)
{
    int x, y, k;
    printf("input y,x,k = ");
    scanf("%d%d%d", &y, &x, &k);
    DFS(1, 1, x, y, k);

    return 0;
}
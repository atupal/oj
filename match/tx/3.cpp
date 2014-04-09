
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int maxn = 6;
int A[maxn][maxn];
int v[maxn][maxn];

void get(int x, int y) {
    A[x][y] += 1;
    if (A[x][y] > 4) {
        A[x][y] = 0;
        if (x - 1 >= 0)
        get(x - 1, y);

        if (x + 1 < maxn)
        get(x + 1, y);

        if (y - 1 >= 0)
        get(x, y - 1);

        if (y + 1 >= 0)
        get(x, y + 1);
    }
}

int main() {
    while (1) {
        for (int i = 0; i < 6; ++ i) {
            for (int j = 0; j < 6; ++ j) 
                if (scanf("%d", &A[i][j]) == EOF) {
                    return 0;
                }
        }
        int m ;
        scanf("%d", &m);
        int x, y;
        while (m --) {
            scanf("%d %d", &x, &y);
            get(x - 1, y - 1);
        }
        for (int i = 0; i < 6; ++ i) {
            for (int j = 0; j < 6; ++ j)
                printf("%d ", A[i][j]);
            printf("\n");
        }
    }

    return 0;
}


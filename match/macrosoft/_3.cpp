
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxn = 101;

int n,m;
int A[maxn][maxn];
int p[maxn][maxn];

int main() {
    int T;
    scanf("%d", &T);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        int x,y;
        scanf("%d %d", &x, &y);
        scanf("%d", &A[x][y]);
    }

    return 0;
}


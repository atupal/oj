
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 100;

int A[maxn][maxn];
int v[4][maxn];
int ans;
int max;
int n;

void dfs(int cur) {
    int i;
    if (cur == n) ans = max > ans ? max : ans;
    else for (i = 0; i < n; ++ i) {
        if (!v[0][i] && !v[1][cur + i] && !v[2][cur - i + n]) {
            max += A[cur][i];
            v[0][i] = v[1][cur + i] = v[2][cur - i + n] = 1;
            dfs(cur + 1);
            v[0][i] = v[1][cur + i] = v[2][cur - i + n] = 0;
            max -= A[cur][i];
        }
    }
}

int main() {
    int tn;
    n = 8;
    scanf("%d", &tn);
    while (tn --) {
        ans = 0;
        for (int i = 0; i < n; ++ i) for (int j = 0; j < n; ++ j) scanf("%d", A[i] + j);
        memset(v, 0, sizeof(v));
        max = 0;
        dfs(0);
        printf("%5d\n", ans);
    }
    return 0;
}


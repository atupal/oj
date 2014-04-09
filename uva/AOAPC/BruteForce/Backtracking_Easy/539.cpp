
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)

const int maxn = 101;

int n,m;
int g[maxn][maxn];
int v[maxn][maxn];
int ans;

void dfs(int t, int cnt, int left) {
    int gcnt = 0;
    for (int i = 0; i < n; ++ i) gcnt += g[t][i];
    for (int i = 0; i < n; ++ i) if (g[t][i] && v[t][i] == 0) {
        v[t][i] = 1;
        v[i][t] = 1;
        dfs(i, cnt + 1, left - gcnt);
        v[t][i] = 0;
        v[i][t] = 0;
    }
    ans = max(ans, cnt);
}

int main () {
    while (scanf("%d %d", &n, &m)) {
        if (n == 0 && m == 0) break;
        memset(g, 0, sizeof(g));
        ans = 0;
        for (int e = 0; e < m; ++ e) {
            int x, y;
            scanf("%d %d", &x, &y);
            g[x][y] = g[y][x] = 1;
        }
        for (int i = 0; i < n; ++ i) {
            memset(v, 0, sizeof(v));
            dfs(i, 0, m);
        }
        printf("%d", ans);
    }
    return 0;
}


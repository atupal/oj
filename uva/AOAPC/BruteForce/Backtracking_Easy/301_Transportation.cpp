/*
14 6 4
5 6 2
4 5 10
4 5 13
5 6 16
0 0 0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)

const int maxn = 101;

int C, S, n;
int u[maxn];
int v[maxn];
int ans;
int maxium;
int cap[maxn];

void dfs(int e, int earn, int left, int g[]) {
    if (e == n) {
        ans = max(ans, earn);
        return;
    }
    if (earn + left <= ans) return;
    int t = g[e] * (v[e] - u[e]);
    int flag = 0;
    for (int i = u[e]; i < v[e]; ++ i) {
        cap[i] -= g[e];
        if (cap[i] < 0) flag = 1;
    }
    if (!flag) {
        dfs(e + 1, earn + t, left - t, g);
    }
    for (int i = u[e]; i < v[e]; ++ i) cap[i] += g[e];
    dfs(e + 1, earn, left - t, g);
}

int main() {
    int g[maxn];
    while(scanf("%d %d %d", &C, &S, &n)) {
        if (!(C + S + n)) break;
        memset(g, 0, sizeof(g));
        ans = 0;
        maxium = 0;
        for (int i = 0; i < n; ++ i) {
            scanf("%d %d %d", &u[i], &v[i], &g[i]);
            maxium += (v[i] - u[i]) * g[i];
        }
        for (int x = 0; x <= S; ++ x) cap[x] = C;
        dfs(0, 0, maxium, g);
        printf("%d\n", ans);
    }
    return 0;
}


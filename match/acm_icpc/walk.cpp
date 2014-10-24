#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 10010;
int T,n,m,d;
int cnt[maxn];
double p[55][maxn];
struct edge {
    int v;
    edge *next;
} e[55];

void clear() {
    for (int i = 0; i < 55; ++ i) {
        for (int j = 0; j < maxn ;++ j) {
            p[i][j] = -.5;
        }
    }
}

void input() {
    if (scanf("%d %d %d", &n, &m, &d) == EOF) {
        exit(0);
    }
    memset(cnt, 0, sizeof(cnt));
    memset(e, 0, sizeof(e));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d %d", &a, &b);
        edge *tmp = (edge *) malloc (sizeof(edge));
        tmp->v = a;
        tmp->next = e[b].next;
        e[b].next = tmp;

        tmp = (edge *) malloc (sizeof(edge));
        tmp->v = b;
        tmp->next = e[a].next;
        e[a].next = tmp;
        ++ cnt[a];
        ++ cnt[b];
    }
    clear();
}

int now;
double  dfs(int deep, int node) {
    if (p[node][deep] > -.1) return  p[node][deep];
    double ret = 0.;
    if (deep) {
        edge *tmp = e[node].next;
        while (tmp) {
            if (tmp->v != now) {
                ret += dfs(deep-1, tmp->v) / (cnt[tmp->v]*1.0);
            }
            tmp = tmp->next;
        }
    } else {
        ret = 1. / n;
    }
    return p[node][deep] = ret;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        input();
        for (int node = 1; node <= n; ++ node) {
            now = node;
            clear();
            double ret = 0.;
            for (int i = 0; i <= d; ++ i) {
                ret += dfs(i, node);
            }
            printf("%.10lf\n", 1. - ret);
        }
    }
    return 0;
}

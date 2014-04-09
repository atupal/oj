
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>

const int maxn = 27;

int A[maxn];
int B[maxn];
int V[maxn][maxn];

void rot(int (*tmp)[3], int x, int a, int b) {
    int t = tmp[x][a];
    tmp[x][a] = -tmp[x][b];
    tmp[x][b] = t;
}

void dfs(int cur, int ans) {
    if (cur == 7) {
        return;
    }
    int tmp[maxn][3];
    int cnt = 0;
    for (int i = 0; i < 27; ++ i) if (A[i]) {
        tmp[cnt][0] = i / 9;
        tmp[cnt][1] = i % 9 / 3;
        tmp[cnt][2] = i % 3;
        ++ cnt;
    }
    for (int i = 0; i < 6; ++ i) {
        if (i < 4) for (int x = 0; x < cnt; ++ x) {
            rot(tmp, x, 0 , 2);
        }
        else if (i < 5)for (int x = 0; x < cnt; ++ x) {
            rot(tmp, x, 1, 2);
        }
        else for (int x = 0; x < cnt; ++ x) {
            rot(tmp, x, 1, 2);
            rot(tmp, x, 1, 2);
        }
        for (int j = 0; j < 4; ++ j) {
            for (int y = 0; y < 6; ++ y) {
                rot(tmp, y, 0 , 1);
            }
            int next = 0;
            for (int k = 0; k < cnt; ++ k) {
                int tp = tmp[k][0] * 9 + tmp[k][1] * 3 + tmp[k][2];
                if (tp < 0 || tp >= maxn)
                    goto here;
                next |= 1 << tp;
            }
            if (next & ans) 
                goto here;
            if (!V[cur][next]) {
                B[cur] = next;
                V[cur][next] = 1;
                dfs(cur + 1, next | ans);
                V[cur][next] = 0;
            }
here:;
        }
    }
    return;
}

int main() {
    char s[maxn + 1];

    while (scanf("%s", s) != EOF) {
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        memset(V, 0, sizeof(V));
        int l = maxn;
        int r = 0;
        int ans;
        for (int i = 0; i < maxn; ++ i) if (s[i] == 'a') {
            A[0] = A[0] | (1 << i);
            l = i < l ? i : l;
            r = i > r ? i : r;
        }
        for (int i = 0; i <= l; ++ i) {
            ans = A[0] >> i;
            dfs(1, ans);
        }
        for (int i = 1; i < maxn  - 1 - r; ++ i) {
            ans = A[0] << i;
            dfs(1, ans);
        }
    }

    return 0;
}


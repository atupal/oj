
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int maxn = 101;

char s[maxn];
char g[maxn][maxn];
char B[maxn];
char A[maxn];
int n;
char v[maxn];
char V[maxn];
int ans;

void dfs(int cur) {
    if (cur == n) {
        int Max = 0;
        for (int i = 0; i < n; ++ i) for (int j = 0; j < n; ++ j) if(g[(int)B[i]][(int)B[j]]){
            if ((i - j > 0 ? i - j : j - i) > Max) Max = i - j > 0 ? i - j : j - i;
        }
        if (Max < ans) {
            ans = Max;
            memcpy(V, B, sizeof(V));
        }
    }

    for (int i = 0; i < 26; ++ i) if (A[i] && !v[i]) {
        B[cur] = i;
        for (int j = 0; j < cur; ++ j) if (g[i][(int)B[j]]) {
             if (cur - j >= ans) goto here;
        }
        v[i] = 1;
        dfs(cur + 1);
        v[i] = 0;
here:;
    }
}

int main() {
    while (scanf("%s", s)) {
        if (strcmp(s, "#") == 0) return 0;
        memset(g, 0, sizeof(g));
        memset(v, 0, sizeof(v));
        memset(A, 0, sizeof(A));
        int i = 0;
        int m = strlen(s);
        n = 0;
        ans = 100000000;
        while (i < m) {
            int t;
            for (t = i + 2; t < m && s[t] != ';'; ++ t) {
                g[s[i] - 'A'][s[t] - 'A'] = 1;
                g[s[t] - 'A'][s[i] - 'A'] = 1;
            }
            i = t + 1;
        }
        for (int i = 0; i < 26; ++ i) 
            for (int j = 0; j < 26; ++ j) if (g[i][j]) {n++; A[i] = 1;break;}
        dfs(0);
        for (int i = 0; i < n; ++ i) printf("%c ", V[i] + 'A');
        printf("-> %d\n", ans);
    }
    return 0;
}


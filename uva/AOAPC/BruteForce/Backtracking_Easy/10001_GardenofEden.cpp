
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 25;

int am[2][2][2];
int a, n;
int isnot;
int first;
int two;
char s[maxn];

void dfs(int cur, int p_1, int p_2) {
    if (isnot) return;
    int s_2 = s[cur - 1];
    if (cur == n) {
        if (am[p_1][p_2][first] == s_2 && am[p_2][first][two]== s[0]) {
            isnot = 1;
        }
        return;
    }
    if (am[p_1][p_2][1] == s_2) dfs(cur + 1, p_2, 1);
    if (am[p_1][p_2][0] == s_2) dfs(cur + 1, p_2, 0);
}

int main () {
    while (scanf("%d %d %s", &a, &n, s) != EOF) {
        for (int i = 0; i < 8; ++ i) {
            am[((i>>2)&1)][((i>>1)&1)][(i & 1)] = ((a>>i)&1);
            //printf("%d %d %d :%d\n", (i>>2)&1, (i>>1)&1, i&1,am[((i>>2)&1)][((i>>1)&1)][(i & 1)] = ((a>>i)&1));
        }
        for (int i = 0; i < n; ++ i) s[i] -= '0';
        isnot = 0;
        first = 0;two=0;
        dfs(2, 0, 0);
        first = 0;two=1;
        dfs(2, 0, 1);
        first = 1;two=0;
        dfs(2, 1, 0);
        first = 1;two=1;
        dfs(2, 1, 1);
        if (isnot) printf("REACHABLE\n");
        else printf("GARDEN OF EDEN\n");
    }
    return 0;
}


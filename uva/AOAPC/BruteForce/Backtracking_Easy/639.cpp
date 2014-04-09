
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
char A[10][10];
int B[10];
int v[10][10];
int ans;

int dfs(int cur) {
    for (int i = 0; i < n; ++ i) 
        for (int j = 0; j < n; ++ j) if(!v[i][j]){
            for (int k = i; k < n && A[k][j] == '.'; ++ k) if (!v[k][j]) v[k][j] = cur + 10;
            for (int k = i; k >= 0 && A[k][j] == '.'; -- k) if (!v[k][j])  v[k][j] = cur + 10;
            for (int k = j; k < n && A[i][k] == '.'; ++ k) if (!v[i][k])  v[i][k] = cur + 10;
            for (int k = j; k >= 0 && A[i][k] == '.'; --k) if (!v[i][k])  v[i][k] = cur + 10;
            dfs(cur + 1);
            for (int x = 0; x < n; ++ x) for (int y = 0; y < n; ++ y) if (v[x][y] == cur + 10) v[x][y] = 0;
        }
    ans = ans > cur ? ans : cur;
    return 0;
}

int main() {
    while (1) {
        scanf("%d", &n);
        if (!n) return 0;
        ans = 0;
        for (int i = 0; i < n; ++ i)
            scanf("%s", A[i]);
        memset(v, 0, sizeof(v));
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                if (A[i][j] != '.') v[i][j] = 1;
        ans = 0;
        dfs(0);
        printf("%d\n", ans);
    }
    return 0;
}


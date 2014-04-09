
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, p;
    int cnt = 0;
    int N[10001];
    int S[10001];
    while (1) {
        ++ cnt;
        scanf("%d %d", &n, &p);
        if (n == 0 && p == 0) return 0;
        memset(N, 0, sizeof(N));
        memset(S, 0, sizeof(S));
        printf("CASE# %d:\n", cnt);
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d", &x);
            ++ N[x];
        }
        S[0] = N[0];
        for (int i = 1; i < 10001; ++ i) {
            S[i] = S[i - 1] + N[i];
        }
        for (int i = 0; i < p; ++ i) {
            int x;
            scanf("%d", &x);
            if (!N[x]) printf("%d not found\n", x);
            else printf("%d found at %d\n", x, x ? S[x - 1] + 1 : 1);
        }
    }
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 101;

int L, W, N;
int x[maxn], w[maxn];
int m[(1 << 20) + 1];
int cur;
int ans[maxn];
double left;
double right;

int dp(int c) {
    if (m[c] != -1) return m[c];
    if (cur == N) return 1;
    //double tleft = 3.0 * W * -1;
    //double tright = 3.0 * W * -1;
    //for (int i = 0; i < N; ++ i) {
    //    if ((c >> i) & 1) {
    //        tleft += (-x[i] - 3) * w[i];
    //        tright += (x[i] - 3) * w[i];
    //    }
    //}
    //if (tleft <= 0 && tright <= 0);
    //else {
    //    m[c] = 0;
    //    return 0;
    //}
    for (int i = 0; i < N; ++ i) {
        if (!((c >> i) & 1)) {
            ans[cur ++] = i;
            left += (-x[i] - 3) * w[i];
            right += (x[i] - 3) * w[i];
            if (left <= 0 && right <= 0 && dp(c | (1 << i))) {
                m[c] = 1;
                return 1;
            }
            else {
                m[c | (1 << i)] = 0;
                left -= (-x[i] - 3) * w[i];
                right -= (x[i] - 3) * w[i];
                cur --;
            }
        }
    }
    m[c] = 0;
    return 0;
}

int main() {
    int cnt = 0;
    while (scanf("%d %d %d", &L, &W, &N)) {
        if (!N) return 0;
        for (int i = 0; i < N; ++ i) 
            scanf("%d %d", &x[i], &w[i]);
        for (int i = 0; i < N; ++ i) x[i] <<= 1;
        memset(m, -1, sizeof(m));
        cur = 0;
        printf("Case %d:\n", ++cnt);
        left = 3.0 * W * -1;
        right = 3.0 * W * -1;
        if (dp(0)) {
            for (int i = N - 1; i >= 0; -- i) 
                printf("%d %d\n", x[ans[i]] / 2, w[ans[i]]);
        }
        else 
            printf("Impossible\n");
    }

    return 0;
}


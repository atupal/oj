
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rep(i, n) for(int i = 0; i < n; ++ i)

int X[101];
int Y[101];
int n;

int get(int A, int B) {
    int cnt = 0;
    int cnt_2 = 0;
    int cnt_3 = 0;
    rep(i, 2 * n) {
        if (A * X[i] + B * Y[i] < 0) ++ cnt;
        else if (A * X[i] + B * Y[i] > 0) ++ cnt_2;
        else ++ cnt_3;
    }
    if (cnt  <= n && n <= cnt + cnt_3) return 1;
    else return 0;
}

int ans(int A, int B) {
    int cnt = 0;
    rep(i, 2 * n) {
        if (A * X[i] + B * Y[i] < 0) ++ cnt;
        if (A * X[i] + B * Y[i] == 0) return 0;
    }
    if (cnt == n) return 1;
    else return 0;
}

int main() {
    while ((scanf("%d", &n), n)) {
        rep(i, n * 2) scanf("%d %d", X + i, Y + i);
        rep(i, 2 * n) if (get(Y[i], -X[i])) {
            if (ans(Y[i]*501 + 1, -X[i]*501)){printf("%d %d\n", Y[i]*501 + 1, -X[i]*501);break;}
            else if (ans(Y[i]*501 - 1, -X[i]*501)){printf("%d %d\n", Y[i]*501 - 1, -X[i]*501);break;}
            else continue;
        }
    }
    
    return 0;
}


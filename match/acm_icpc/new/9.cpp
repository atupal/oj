#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const long long MOD = 10000007;
int n,m;
long long a[13];
long long t[13][13];
long long st[13][13];

void exp(long long ret[][13], long long x[][13]) {
    long long ret_tmp[13][13];
    for (int i = 0; i <= n+1; ++ i) {
        for (int j = 0; j <= n+1; ++ j) {
            long long sum = 0;
            for (int k = 0; k <= n+1; ++ k) {
                sum = (sum + ret[i][k] * x[k][j]);
            }
            sum %= MOD;
            ret_tmp[i][j] = sum;
        }
    }
    memcpy(ret, ret_tmp, sizeof(ret_tmp));
}

void solve() {
    a[0] = 233;
    for (int i = 1; i <= n; ++ i) {
        scanf("%lld", a+i);
    }
    a[n+1] = 1;

    memset(t, 0, sizeof(t));
    t[0][0] = 10;
    t[0][n+1] = 3;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j <= i; ++ j) {
            t[i][j] = 1;
        }
    }
    t[n+1][n+1] = 1;

    memcpy(st, t, sizeof(t));
    m -= 1;
    while (m) {
        if (m&1) exp(st, t);
        exp(t, t);
        m >>= 1;
    }

    long long sum = 0;
    for (int i = 0; i <= n+1; ++ i) {
        sum = (sum + st[n][i] * a[i]);
    }
    sum %= MOD;
    printf("%lld\n", sum);
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        solve(); 
    }
    return 0;
}

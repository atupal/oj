#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int n,m,k;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

long long C2 (int x) {
    if (x < 2) return 0;
    return (long long ) x * (x - 1) >> 1;
}

void solve() {
    long long ans = 0;
    int Min = min(n, m);
    int Max = max(n, m);
    if (Min < 2 || k < 4) {
        printf("0\n");
        return;
    }
    int t = (int)sqrt(k);
    t = min(t - 2, Min);
    long long tmp = 0;
    for (t = 2; t <= Min; ++ t) {
        if (t > 0 && k / t + !(!(k % t)) <= Max){
            tmp = 1LL * C2(t) * C2(k / t);
            if (0 && k / t < t && t + 1 <= Min) {
                tmp += C2(k % t) * t;
            }
            else 
                tmp += C2(k % t) * (k / t);
            ans = tmp > ans ? tmp : ans;
        }
    }

    printf("%lld\n", ans);
    return;
}


int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; ++ i) {
        scanf("%d %d %d", &n, &m, &k);
        printf("Case #%d: ", i + 1);
        solve();
    }

    return 0;
}
    

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

void gcdEx(long long a, long long n, long long &g, long long &tt) {
    long long t = 0, newt = 1, r = n, newr = a;
    while (newr != 0) {
        long long q = r / newr;
        long long tmp;
        tmp = t;
        t = newt;
        newt = tmp - q * newt;

        tmp = r;
        r = newr;
        newr = tmp - q * newr;
    }

    if (t < 0) {
        t += n;
    }

    g = r;
    tt = t;
}

void solve() {
    long long x, y, m, n, L;
    scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &L);
    if (m == n) {
        printf("Impossible\n");
        return;
    }

    long long d = m - n, s = y - x;
    if (d < 0) d += L * (-d / L + 1);
    if (s < 0) s += L * (-s / L + 1);
    long long g, t;
    gcdEx(d, L, g, t);
    if (s % g != 0) {
        printf("Impossible\n");
        return;
    }
    long long ans = t * (s / g) % (L / g);
    printf("%lld\n", ans);
}

int main() {
    std::ios::sync_with_stdio(false);

    solve();

    return 0;
}

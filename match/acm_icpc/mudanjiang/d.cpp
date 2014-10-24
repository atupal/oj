#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline
int max(int a, int b) {
    return a > b ? a : b;
}

inline
int min(int a, int b) {
    return a < b ? a : b;
}

double mo[51][51];

inline
double dp(int n, int m) {
    if (mo[n][m] > -.1) return mo[n][m];
    double ret = 0.;
    return ret;
}

void init() {
    for (int i = 0; i < 51; ++ i) {
        for (int j = 0; j < 51; ++ j) {
            mo[i][j] = -.5;
        }
    }
}

void solve() {
    int n, m;
    scanf("%d %d", &n, &m);
}

int main() {
    int t;
    scanf("%d", &t);
    init();
    while (t--) {
        solve();
    }
    return 0;
}

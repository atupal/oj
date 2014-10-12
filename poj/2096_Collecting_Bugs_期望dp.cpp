
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn  = 1010;
int n,s;

double mo[maxn][maxn];

inline
double dp(int i, int j) {
    if (i > n || j > s) return 0;
    if (mo[i][j] > -.1) return mo[i][j];
    double ret = 0.;
    double ns = n * s;
    ret += 1.;
    ret += dp(i+1, j+1) * (n-i)*(s-j)/ns;
    ret += dp(i, j+1) * i*(s-j)/ns;
    ret += dp(i+1, j) * (n-i)*j/ns;
    ret /= (1-i*j/ns);
    return mo[i][j] = ret;
}

void solve() {
    for (int i = 0; i < maxn; ++ i) {
        for (int j = 0; j < maxn; ++ j) {
            mo[i][j] = -.5;
        }
    }
    mo[n][s] = 0.;
    printf("%.4lf\n", dp(0, 0));
} 

int main() {
    scanf("%d %d", &n, &s);
    solve();
    return 0;
}

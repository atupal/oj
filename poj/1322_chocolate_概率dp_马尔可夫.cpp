#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 1010;
double dp[maxn][maxn];
int c, n , m;

void solve() {

  if (m > c) {
    printf("%.3lf\n", 0.);
    return;
  }

  if (n > 1000) n = 1000+(n&1);

  for (int i = 0; i <= c; ++ i) {
    dp[0][i] = 0;
  }
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++ i) {
    for (int j = 0; j <= c; ++ j) {
      dp[i][j] = 0;
      if (j-1>=0)
        dp[i][j] += dp[i-1][j-1] * (c-j+1)/(double)c;
      if (j+1<=c)
        dp[i][j] += dp[i-1][j+1] * (j+1)/(double)c;
    }
  }

  printf("%.3lf\n", dp[n][m]);
}

int main() {
  while (1) {
    scanf("%d %d %d", &c, &n, &m);
    if (c == 0) return 0;
    solve();
  }

  return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a[101][101];
int ans, n;
int dp[101][101];

void solve() {
  ans = -127;
  memset(dp, 0, sizeof(dp));

  dp[1][1] = a[1][1];
  for (int i = 2; i <= n; ++ i) {
    dp[1][i] = dp[1][i-1] + a[1][i];
    dp[i][1] = dp[i-1][1] + a[i][1];
  }

  for (int i = 2; i <= n; ++ i) {
    for (int j = 2; j <= n; ++ j) {
      dp[i][j] = dp[i][j-1] + dp[i-1][j] + a[i][j] - dp[i-1][j-1];
    }
  }

  for (int i = 0; i <= n; ++ i) {
    for (int j = 0; j <= n; ++ j) {
      for (int k = i+1; k <= n; ++ k) {
        for (int l = j+1; l <= n; ++ l) {

          int sum=  dp[k][l] - dp[k][j] - dp[i][l] + dp[i][j];
          ans = sum > ans ? sum : ans;

        }
      }
    }
  }

  printf("%d\n", ans);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= n; ++ j) {
      scanf("%d", &a[i][j]);
    }
  }

  solve();

  return 0;
}

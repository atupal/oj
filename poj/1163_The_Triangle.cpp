#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 101;

int dp[maxn][maxn];

int n;
int s[maxn][maxn];

void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j <= i; ++ j) {
      scanf("%d", s[i]+j);
    }
  }

  memset(dp, 0, sizeof(dp));
}

inline
int max(int a, int b) {
  return a > b ? a : b;
}

void solve() {
  dp[0][0] = s[0][0];
  for (int i = 0; i < n-1; ++ i) {
    for (int j = 0; j <= i; ++ j) {
      dp[i+1][j] = max(dp[i+1][j], dp[i][j] + s[i+1][j]);
      dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + s[i+1][j+1]);
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++ i) {
    if (dp[n-1][i] > ans) {
      ans = dp[n-1][i];
    }
  }

  printf("%d\n", ans);
}

int main() {
  input();
  solve();

  return 0;
}

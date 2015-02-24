/*
ID: atupal1
PROG: numtri
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 1002;
int n;
int map[maxn][maxn];
int dp[maxn][maxn];

inline
int max(int a, int b) {
  return a > b ? a : b;
}

void solve() {
  memset(dp, 0, sizeof(dp));
  dp[0][0] = map[0][0];
  for (int i = 0; i < n-1; ++ i) {
    for (int j = 0; j <= i; ++ j) {
      dp[i+1][j] = max(dp[i+1][j], dp[i][j] + map[i+1][j]);
      dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + map[i+1][j+1]);
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
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("numtri.in", "r", stdin);
    freopen("numtri.out","w", stdout);
  }
  scanf("%d", &n);
  memset(map, 0, sizeof(map));
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j <= i; ++ j) {
      scanf("%d", map[i]+j);
    }
  }
  solve();

  return 0;
}


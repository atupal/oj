#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 110;
int n, m;
int a[maxn][maxn];
int s[maxn];

int dp[maxn][maxn];

inline
int max(int a, int b) {
  return a > b ? a : b;
}

void solve() {
  scanf("%d %d", &n, &m);
  memset(s, 0, sizeof(s));
  memset(a, 0, sizeof(a));
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= m; ++ i) {
    for (int j  = 1; j <= m ; ++ j) {
      scanf("%d", a[i]+j);
    }
  }

  for (int i = 1; i <= n; ++ i)
    scanf("%d", s+i);

  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= m; ++ j) {
      if (s[i] < 0) {
        if (s[i-1] < 0) {
          for (int x = 1; x <=m; ++ x) {
            for (int y = 1; y <=m; ++ y) {
              dp[i][x] = max(dp[i][x], dp[i-1][y] + a[y][x]);
            }
          }
        } else {
          for (int x = 1; x <= m; ++ x) {
            dp[i][x] = max(dp[i][x], dp[i-1][s[i-1]] + a[s[i-1]][x]);
          }
        }
      } else {
        if (s[i-1]<0) {
          for (int x = 1; x <= m; ++ x) {
            dp[i][s[i]] = max(dp[i][s[i]], dp[i-1][x] + a[x][s[i]]);
          }
        } else {
          dp[i][j] = max(dp[i][j], dp[i-1][s[i-1]] + a[s[i-1]][s[i]]);
        }
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= m; ++ i) {
    ans = max(ans, dp[n][i]);
  }
  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 1010;
char a[maxn], b[maxn];
int len_a, len_b;
int dp[maxn][maxn];

inline
int min(int a, int b) {
  return a < b ? a : b;
}

void solve() {
  for (int i = 0; i <= len_a; ++ i) {
    dp[i][0] = i;
  }
  for (int i = 1; i <= len_b; ++ i) {
    dp[0][i] = i;
  }
  for (int i = 1; i <= len_a; ++ i) {
    for (int j = 1; j <= len_b; ++ j) {
      dp[i][j] = dp[i-1][j-1] + (a[i-1]!=b[j-1]);
      dp[i][j] = min(dp[i][j], min(dp[i-1][j], dp[i][j-1])+1);
    }
  }
  printf("%d\n", dp[len_a][len_b]);
}

int main() {
  while (scanf("%d %s", &len_a, a) != EOF) {
    scanf("%d %s", &len_b, b);
    solve();
  }
  return 0;
}

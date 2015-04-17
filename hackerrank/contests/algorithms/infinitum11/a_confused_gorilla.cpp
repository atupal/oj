#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 1010;
int n;
int memo[maxn][maxn];

int dp(int x, int y) {
  if (x < 0 || y < 0) return 0;
  int &ret = memo[x][y];
  if (ret != -1) return ret;

  return ret = dp(x-1, y) + dp(x, y-1);
}

void solve() {
  /* test
  memset(memo, -1, sizeof(memo));
  memo[0][0] = 1;
  for (int i = 0; i <= n; ++ i) {
    printf("%d %d -> %d\n", i, n-i, dp(i, n-i));
  }
  */
  if (n&1) {
    // n = 5: 0 1 2 3 4 5
    for (int i = 0; i <= n/2; ++ i) {
      printf("%d %d\n", i, n-i);
      printf("%d %d\n", n-i, i);
    }
  } else {
    // n = 4: 0 1 2 3 4
    for (int i = 0; i < n/2; ++ i) {
      printf("%d %d\n", i, n-i);
      printf("%d %d\n", n-i, i);
    }
    printf("%d %d\n", n/2, n/2);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++ i) {
    scanf("%d", &n);
    solve();
  }

  return 0;
}


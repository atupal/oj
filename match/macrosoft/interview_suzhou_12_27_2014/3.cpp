#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 110;
const int MOD = (long long) 1e9 + 7L;
typedef long long int64;
int64 n, m;
int64 dp[maxn][maxn][maxn];

inline 
int64 gcd(int64 a, int64 b) {
  if (a < b) a ^= b ^= a ^= b;
  return b == 0 ? a : gcd(b, a%b);
}

inline
int64 min(int64 a,int64 b) {
  return a < b ? a : b;
}

inline
int64 get(int64 i, int64 n, int64 r) {
  if (dp[i][n][r] != -1) return dp[i][n][r];
  if (i>n) return 0L;
  int64 ans = 0; 
  for (int64 y=1; y<=m; ++ y) {
    if (gcd(y*i, m) == r) {
      for (int64 x=min(i-1, n-i); x>0; --x) {
        ans += get(x, n-i, y);
        if (ans >= MOD) ans -= MOD;
      }
    }
  }
  return dp[i][n][r] = ans;
}

int main() {
  scanf("%lld %lld", &n, &m);

  memset(dp, -1, sizeof(dp));
  /*
  dp[1][1][1] = 1;
  for (int r = 2; r <= m; ++ r) {
    dp[1][1][r] = 0;
  }
  */
  for (int i = 1; i <= n; ++ i) {
    dp[i][i][gcd(i, m)] = 1;
  }

  int64 ans = 0;
  for (int i = 1; i <= n; ++ i) {
    ans += get(i, n, m);
  }
  printf("%lld\n", ans);

  return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long int64;
const int64 MOD = (int64)1e9+7;

int64 n;

int64 exp(int64 n) {
  int64 ret = 1;
  int64 base = 2;
  while (n) {
    if (n&1) {
      ret *= base;
      ret %= MOD;
    }
    base *= base;
    base %= MOD;
    n >>= 1;
  }

  return ret;
}

/*
 * dp[n][i] means total n marbles, and first pick up the ith marble's solution counter.
 * obviousely:
 *    dp[n][i] = dp[n-1][i] + dp[n-1][i-1]
 * since C(n, r) = C(n-1, r) + C(n-1, r-1)
 * But note that dp[n][0] = 0 not like C(n, 0) = 1
 * so the answer is dp[n][1] + dp[n][2] + dp[n][3] + ... + dp[n][n] = sum{C(n-1, i) | i <- [0, n-1]} = 2**(n-1)
 * */
void solve() {
  scanf("%lld", &n);
  printf("%lld\n", exp(n-1));
}

int main() {
  int t;
  scanf("%d", &t);
  for (int cas=1; cas <= t; ++ cas) {
    solve();
  }

  return 0;
}


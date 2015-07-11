#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long int64;
const int64 MOD = (int64) 1e9 + 7;
int n, k;

int64 exp(int64 a, int64 n) {
  int64 ret = 1;
  int64 base = a;
  while (n) {
    if (n&1) {
      ret *= base;
      ret %= MOD;
    }
    base = base*base%MOD;
    n >>= 1;
  }

  return ret;
}

int gcd(int a, int b) {
  while (a && b) a%=b^=a^=b^=a;

  return a+b;
}

/*
 * Burnside's lemma
 * */
void solve() {
  int64 ans = 0;
  for (int i = 1; i <= n; ++ i) {
    ans += exp(k, gcd(i, n));
    if (ans >= MOD) ans -= MOD;
  }

  printf("%lld\n", ans*exp(n, MOD-2)%MOD);
}

int main() {
  scanf("%d %d", &n, &k);
  solve();

  return 0;
}


/*
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 100000000;
int n, m;

int prime[20];
int prime_cnt;

long long exp(long long a, int n) {
  long long ret = 1;
  while (n) {
    if (n&1) ret *= a;
    a *= a;
    n >>= 1;
  }
  return ret;
}

void solve() {
  prime_cnt = 0;
  int t = m;
  for (int i = 2; i*i <= m; ++ i) {
    if (t%i == 0) {
      prime[prime_cnt++] = i;
      while (t%i == 0) t/=i;
    }
  }
  if (t > 1) prime[prime_cnt++] = t;

  long long ans = 0;
  int u = 1<<prime_cnt;
  for (int i = 1; i < u; ++ i) {
    int cnt = 0;
    int mul = 1;
    for (int j = 0; j < prime_cnt; ++ j) {
      if ((i>>j)&1) {
        ++ cnt;
        mul *= prime[j];
      }
    }
    if (cnt&1) {
      ans += exp(m/mul, n);
    } else {
      ans -= exp(m/mul, n);
    }
  }
  printf("%lld\n", exp(m, n) - ans);
}

int main() {
  while (scanf("%d %d", &n, &m) != EOF)
    solve();

  return 0;
}

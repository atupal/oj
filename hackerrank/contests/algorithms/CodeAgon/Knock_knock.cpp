#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long int64;

const int64 MOD = (int64) 1e9;

int64 r[] = {1, 1, 1, 3, 3, 3*5, 3*5, 3*5*7, 3*5*7, 3*5*7, 3*5*7};

int64 exp(int64 x, int64 n) {
  if (x==0) return 0L;
  int64 base = x;
  int64 ret = 1;
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

int64 R(int64 n) {
  if (n <= 10) return r[n];
  int64 ret = exp(2, (n+3)/4);

  ret *= R((n+4)/5); ret %= MOD;
  ret *= R((n+9)/10); ret %= MOD;

  return ret;
}

inline
int64 max(int64 a, int64 b) {
  return a > b ? a : b;
}

void solve(int64 n) {
  int64 ans = 0;
  for (int i = 1; i <= 5; ++ i) {
    for (int j = 1; j <= 5; ++ j) {
      if (!(i%2==0 && j%2==0) && (i!=j || (i==1 && j==1))) {
        ans = max(ans, exp(n*i, n*j));
      }
    }
  }
  printf("%llu\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int64 n;
    scanf("%llu", &n);
    solve(R(n));
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const long long MOD = 1e9+7;

long long squares_sum(long long n) {
  // the modular mulitiplicative inverse of 6 modulo 10e9+7
  long long ret = 166666668;
  ret = (ret * (n%MOD)) % MOD;
  ret = (ret * ((n+1)%MOD)) % MOD;
  ret = (ret * ((2*n+1)%MOD)) % MOD;

  return ret;
}

long long nature_numbers_sum(long long n) {
  // the modular mulitiplicative inverse of 2 modulo 10e9+7
  long long ret = 500000004;
  ret = (ret * (n%MOD)) % MOD;
  ret = (ret * ((n+1)%MOD)) % MOD;

  return ret;
}

void solve(long long l, long long r) {

  long long ss = (squares_sum(r) - squares_sum(l-1) + MOD) % MOD;
  long long ns = (nature_numbers_sum(r) - nature_numbers_sum(l-1) + MOD) % MOD;

  ss = (ss*15)%MOD;
  ns = (ns*4)%MOD;

  long long cs = (4*((r-l+1)%MOD)) % MOD;

  long long ret = ss;
  ret = (ret + ns) % MOD;
  ret = (ret - cs + MOD) % MOD;

  printf("%lld\n", ret);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 0; t < T; ++ t) {
    long long l, r;
    scanf("%lld %lld", &l, &r);
    solve(l, r);
  }

  return 0;
}


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


/*
 * x = sqrt(2k/6)
 * y = sqrt(3k/6)
 * z = sqrt(k/6)
 *
 *
 * (  12(x+z)(y+z) - 6(x+y)^2  )^2 + 6(  12(x+z)(y+z) - 6(x+y)^2  ) (x^2+y^2+z^2)    -  96sqrt(3)xy^2z  + 2(3xz + sqrt(2)y^2)^2 + 4sqrt(6)xy - 4
 *
 *
 *
 *
 * replaced with k:
 *
 *



(  12(sqrt(2k/6)+sqrt(k/6))(sqrt(3k/6)+sqrt(k/6)) - 6(sqrt(2k/6)+sqrt(3k/6))^2  )^2 




(-3+2 sqrt(2)+2 sqrt(3))^2 k^2


+ 6(  12(sqrt(2k/6)+sqrt(k/6))(sqrt(3k/6)+sqrt(k/6)) - 6(sqrt(2k/6)+sqrt(3k/6))^2  ) (sqrt(2k/6)^2+sqrt(3k/6)^2+sqrt(k/6)^2)   


6(-3+2 sqrt(2)+2 sqrt(3)) k^2


 -  96sqrt(3)sqrt(2k/6)sqrt(3k/6)^2sqrt(k/6)  
 
 8 sqrt(6) k^2
 
 
 + 2(3sqrt(2k/6)sqrt(k/6) + sqrt(2)sqrt(3k/6)^2)^2 + 4sqrt(6)sqrt(2k/6)sqrt(3k/6) - 4
 
 
 4 (k^2+k-1)
 
 
 
 
 (-3+2 sqrt(2)+2 sqrt(3))^2 k^2 + 6(-3+2 sqrt(2)+2 sqrt(3)) k^2  -  96sqrt(3)sqrt(2k/6)sqrt(3k/6)^2sqrt(k/6)  +  4 (k^2+k-1)
 
 
 
 15 k^2+4 k-4
 *
 *
 *
 * final reults:
 *
 * https://www.wolframalpha.com/input/?i=simplify+(-3%2B2+sqrt(2)%2B2+sqrt(3))%5E2+k%5E2+%2B+6(-3%2B2+sqrt(2)%2B2+sqrt(3))+k%5E2++-++96sqrt(3)sqrt(2k%2F6)sqrt(3k%2F6)%5E2sqrt(k%2F6)++%2B++4+(k%5E2%2Bk-1)
 *
 * */

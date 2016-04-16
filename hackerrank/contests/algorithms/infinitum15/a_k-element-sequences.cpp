#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int max = 2000009;

//http://stackoverflow.com/questions/35226781/finding-binomial-coefficient-for-large-n-and-k-modulo-m
//
const long long MOD = (long long)1e9 + 7;

// Extended Euclidean algorithm
long long xGCD(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }

  long long x1, y1, gcd = xGCD(b, a % b, x1, y1);
  x = y1;
  y = x1 - (long long)(a / b) * y1;
  return gcd;
}

// factorial of n modulo MOD
long long modfact[max];
void init_modfact(int n) {
  modfact[0] = 1;
  long long cal = 1;
  for (long long i = 1; i < n; ++ i) {
    cal = cal * i % MOD;
    modfact[i] = cal;
  }
}

// multiply a and b modulo MOD
long long modmult(long long a, long long b) {
  return (long long)a * b % MOD;
}

// inverse of a modulo MOD
long long inverse(long long a) {
  long long x, y;
  xGCD(a, MOD, x, y);
  return x;
}

// binomial coefficient nCk modulo MOD
long long bc(long long n, long long k)
{
  long long ret = modmult(modmult(modfact[n], inverse(modfact[k])), inverse(modfact[n - k]));
  return (ret+MOD)%MOD;
}

int main() {
  int T;
  scanf("%d", &T);

  init_modfact(max);

  for (int t = 0; t < T; ++ t) {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    printf("%lld\n", bc(n-1, k-1));
  }

  return 0;
}

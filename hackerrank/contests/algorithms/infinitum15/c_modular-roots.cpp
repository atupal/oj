#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

const int maxn = 5000009;
long long p, root;
long long n, k;
long long h[maxn];
int cnt;
long long output[maxn];

long long exp(long long a, long long b);
long long gcd(long long a, long long b) {
  while (a && b) b ^= a ^= b ^= a = a%b;

  return a+b;
}

// http://math.stackexchange.com/questions/124408/finding-a-primitive-root-of-a-prime-number
long long facts[maxn];
int fcnt = 0;
long long primitive_root(long long p) {
  long long s = p - 1;

  long long bd = (long long)sqrt(s)+1;
  for (int i = 2; i < bd; ++ i) {
    if (s % i == 0)
    {
      while (s % i == 0) {
        s /= i;
      }
      facts[fcnt++] = (p-1)/i;
    }
  }

  if (s != 1) {
    facts[fcnt++] = (p-1)/s;
  }

  for (int i = 2; i < p; ++ i) {
    int flag = 1;
    for (int j = 0; j < fcnt; ++ j) {

      if (exp(i, facts[j]) == 1) {
        flag = 0;
        break;
      }

    }

    if (flag) {
      return (long long) i;
    }

  }

  return 0;
}

long long exp(long long a, long long b) {

  long long ret = 1;
  long long base = a;

  while (b) {
    if (b & 1) {
      ret = (ret * base) % p;
    }
    base = base*base % p;
    b >>= 1;
  }

  return ret;
}

long long gcdExtended(long long a, long long b, long long *x, long long *y);

// Function to find modulo inverse of a
long long modInverse(long long a, long long m)
{
    long long x, y;
    long long g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        printf("Inverse doesn't exist");
    else
    {
        // m is added to handle negative x
        long long res = (x%m + m) % m;
        while (res < 0) res += m;
        return res;
    }

    return 0;
}

// C function for extended Euclidean Algorithm
long long gcdExtended(long long a, long long b, long long *x, long long *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    long long x1, y1; // To store results of recursive call
    long long gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

// http://math.stackexchange.com/questions/158344/how-to-find-the-solutions-for-the-n-th-root-of-unity-in-modular-arithmetic
// http://mathafou.free.fr/themes_en/kcongr.html
void solve(long long k, long long n) {
  while (n < 0) n += p;
  n %= p;
  k %= p-1;

  long long d = gcd(k, p-1);
  long long H = h[(int)n];
  if (H % d != 0) {
    printf("NONE\n");
    return;
  }
  long long K = H/d*modInverse(k/d, (p-1)/d)%((p-1)/d);

  cnt = 0;
  for (int i = 0; i < d; ++ i) {
    K += (p-1)/d;
    output[cnt++] = exp(root, K);
  }

  sort(output, output+cnt);

  for (int i = 0; i < cnt; ++ i) {
    printf("%lld ", output[i]);
  }
  printf("\n");

}

void init() {
  scanf("%lld", &p);
  root = primitive_root(p);

  for (int i = 1; i < p; ++ i) {
    long long e = exp(root, i);
    h[e] = i;
  }

}

int main() {
  init();

  int Q;
  scanf("%d", &Q);

  for (int i = 0; i < Q; ++ i) {
    long long k, n;
    scanf("%lld %lld", &k, &n);
    solve(k, n);
  }

  return 0;
}


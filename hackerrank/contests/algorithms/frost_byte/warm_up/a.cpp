
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MOD = 100007;
int n;
typedef long long int64;

int64 exp(int64 a, int64 n) {
  int64 ans=1, base=a;
  while (n) {
    if (n&1) {
      ans*=base;
      ans%=MOD;
    }
    base*=base;
    base%=MOD;
    n>>=1;
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  int sum = 0;
  for (int i = 0; i < n; ++ i) {
    int t;
    scanf("%d", &t);
    sum += t;
  }
  int r = sum%n;
  int q = sum/n;
  printf("%lld\n", (exp(q+1, r) * exp(q, n-r))%MOD);

  return 0;
}

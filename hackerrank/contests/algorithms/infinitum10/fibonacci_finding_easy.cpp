#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;
const ll MOD = (ll)1e9+7;
ll a, b, n;
ll A[2][2], ret[2][2], base[2][2], tmp[2][2];

void solve() {
  A[0][0] = 0;
  A[0][1] = 1;
  A[1][0] = 1;
  A[1][1] = 1;
  memcpy(ret, A, sizeof(A));
  memcpy(base, A, sizeof(A));
  if (n == 1) {
    printf("%lld\n", b);
    return;
  }
  n -= 1;
  while (n) {
    if (n&1) {
      tmp[0][0] = (ret[0][0] * base[0][0] % MOD + ret[0][1] * base[1][0] % MOD )%MOD;
      tmp[0][1] = (ret[0][0] * base[0][1] % MOD + ret[0][1] * base[1][1] % MOD )%MOD;
      tmp[1][0] = (ret[1][0] * base[0][0] % MOD + ret[1][1] * base[1][0] % MOD )%MOD;
      tmp[1][1] = (ret[1][0] * base[0][1] % MOD + ret[1][1] * base[1][1] % MOD )%MOD;
      memcpy(ret, tmp, sizeof(tmp));
    }
    tmp[0][0] = (base[0][0] * base[0][0] % MOD + base[0][1] * base[1][0] % MOD)%MOD;
    tmp[0][1] = (base[0][0] * base[0][1] % MOD + base[0][1] * base[1][1] % MOD)%MOD;
    tmp[1][0] = (base[1][0] * base[0][0] % MOD + base[1][1] * base[1][0] % MOD)%MOD;
    tmp[1][1] = (base[1][0] * base[0][1] % MOD + base[1][1] * base[1][1] % MOD)%MOD;
    memcpy(base, tmp, sizeof(tmp));
    n >>= 1;
  }
  ll ans = (ret[0][0] * a % MOD + ret[0][1] * b % MOD) % MOD;
  printf("%lld\n", ans);

}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++ i) {
    scanf("%lld %lld %lld", &a, &b, &n);
    solve();
  }

  return 0;
}


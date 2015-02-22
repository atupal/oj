#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long long ll;
ll MOD = (ll)1e9+7;
ll n;

ll exp(ll t) {
  ll base = 2ll;
  ll ret = 1ll;
  while (t) {
    if (t&1) {
      ret = base*ret%MOD;
    }
    base = base*base%MOD;
    t >>= 1ll;
  }
  return ret;
}

// ans is 2^( 2^n - n)
void solve() {
  MOD --;
  ll ret = (exp(n) + MOD - n%MOD) % MOD;
  MOD ++;
  ret = exp(ret);
  printf("%lld\n", ret);
}

int main() {
  int t;
  scanf("%d", &t);
  for (;t--;) {
    scanf("%lld", &n);
    solve();
  }

  return 0;
}


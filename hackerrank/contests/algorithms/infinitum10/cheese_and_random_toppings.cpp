#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef long long ll;
const int maxn = 51;
ll r, n, m;
ll C[maxn][maxn];

void solve() {
  ll ans = 0;
  ll tmp = m;
  for (ll mi = 2; mi < maxn; ++ mi) if (tmp%mi == 0) {
    tmp /= mi;
    ll t;
    for (t = 1; t <= mi; ++ t) {
      if ( (m/mi*t)%mi == 1 ) {
        break;
      }
    }

    ll ri = r;
    ll ni = n;
    ll a = 1;
    while (ni) {
      a *= C[ni%mi][ri%mi]%mi;
      ni /= mi;
      ri /= mi;
    }
    a %= mi;

    ans += a*t*(m/mi);
    ans %= m;

  }

  printf("%lld\n", ans);

}

void init() {
  memset(C, 0, sizeof(C));
  C[0][0] = 1ll;
  for (int i = 1; i < maxn; ++ i) {
    for (int j = 0; j < maxn; ++ j) {
      C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
  }
}

int main() {
  init();

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++ i) {
    scanf("%lld %lld %lld", &n, &r, &m);
    solve();
  }

  return 0;
}


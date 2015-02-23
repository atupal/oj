#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll maxn = 101ll;
const ll MOD = (ll)1e9+7ll;
ll cnt;
ll a[maxn];
ll mul[maxn];
map<pair<ll, ll>, ll> memo;

ll fib(ll n);
ll gcdEx(ll a, ll b, ll *x, ll *y);

// 用欧拉公式求模逆元，但这里 x 太大，模了一下，不知道对不对，所以先用上面的拓展欧几里得
ll exp(ll x) {
  ll n = MOD-2;
  ll ret = 1ll;
  ll base=x;
  while (n) {
    if (n&1) ret = ret*base%MOD;
    base = base*base%MOD;
    n >>= 1;
  }
  return ret;
}

ll gcd(ll a, ll b) {
  if (a < b) a ^= b ^= a ^= b;
  return b == 0 ? a : gcd(b, a%b);
}

/*
   Let A(g, i) = gcd(Fg, lcm(Fa1, Fa2,...,Fai)).
   then the ans is A(0, N)
   Let X = lcm(Fa1, Fa2,...,Fai-1).
   use distributive lattice, we have:
   A(g, i) = gcd(Fg, lcm(Fai, X)) = lcm(Fgcd(g, ai), gcd(Fg, X))
           = Fgcd(g, ai) * gcd(Fg, X) / gcd(Fgcd(g, ai), gcd(Fg, X) )
           = Fgcd(g, ai) * gcd(Fg, X) / gcd(Fgcd(g, ai), Fg, X)
           = Fgcd(g, ai) * gcd(Fg, X) / gcd(Fgcd(g, ai), X)
           = Fgcd(g, ai) * A(g, i-1) / A(gcd(g, ai), i-1)

   So if i == 0: A(g, i) = 1
   else A(g, i) = Fgcd(g, ai) * A(g, i-1) / A(gcd(g, ai), i-1)
 */
ll A(ll g, ll i) {
  if (i == -1) return 1ll;
  if (memo[make_pair(g, i)]) {
    return memo[make_pair(g, i)];
  }

  ll q = A( gcd(g, a[i]), i-1 );
  ll x, y;
  gcdEx(MOD, q, &x, &y);
  while (y < 0) y += MOD;
  return memo[make_pair(g, i)] = fib(gcd(g, a[i])) * A(g, i-1) % MOD * y % MOD;
}

void solve() {
  printf("%lld\n", A(0, cnt-1));
}


int main() {
  /*
  printf("%lld %lld\n", fib(15), fib(5));
  printf("%lld\n", fib(15)/fib(5));
  printf("%lld\n", fib(15) * exp(fib(5)) % MOD);
  */

  int n;
  scanf("%d", &n);
  cnt = 0;
  for (int i = 0; i < n; ++ i) {
    scanf("%lld", a+cnt);
    int flag = 0;
    for (int i = 0; i < cnt; ++ i) {
      if (a[i] == a[cnt]) {
        flag = 1;
        break;
      }
    }
    if (flag) continue;
    if (a[cnt] > 2) {
      cnt += 1;
    }
  }
  if (cnt == 0) {
    printf("1\n");
  } else if (cnt == 1) {
    printf("%lld\n", fib( a[0] ));
  } else {
    solve();
  }

  return 0;
}

ll fib(ll n) {
  if (n == 0) return 0ll;
  ll a = 1, b = 1;
  ll A[2][2], ret[2][2], base[2][2], tmp[2][2];
  
  A[0][0] = 0;
  A[0][1] = 1;
  A[1][0] = 1;
  A[1][1] = 1;
  memcpy(ret, A, sizeof(A));
  memcpy(base, A, sizeof(A));
  if (n <= 2) {
    return 1ll;
  }
  n -= 2;
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
    n >>= 1ll;
  }
  ll ans = (ret[0][0] * a % MOD + ret[0][1] * b % MOD) % MOD;
  return ans;
}

ll gcdEx(ll a, ll b, ll *x, ll *y) {
  if(b==0) {
    *x = 1ll,*y = 0ll;
    return a;
  } else {
    ll r = gcdEx(b, a%b, x, y);
    ll t = *x;
    *x = *y;
    *y = t - a/b * *y;
    return r;
  }
}

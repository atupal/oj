#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 101;
const ll MOD = (ll)1e9+7;
//const ll MOD = 19ll;
int cnt;
ll a[maxn];
ll a_copy[maxn];
ll mul[maxn];
map<ll, int> facts;

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

ll get() {
  ll g = fib(a[0]);
  for (int i = 1; i < cnt; ++ i) {
    g = gcd(g, fib(a[i]));
  }
  ll ans = g;
  for (int i = 0; i < cnt; ++ i) {
    ans *= fib(a[i])/g;
    ans %= MOD;
  }
  return ans;
}

void solve() {
  for (int i = 0; i < cnt; ++ i) {
    ll n = a[i];
    for (ll j = 2; j*j <= a[i]; ++ j) {
      while (n%j==0) {
        facts[j] = 1;
        n /= j;
      }
    }
    if (n > 1) {
      facts[n] = 1;
    }
  }


  memcpy(a_copy, a, sizeof(a));
  for (int i = 0; i < cnt; ++ i) {
    mul[i] = 1;
  }

  ll ans = 1;
  for (__typeof(facts.begin()) it = facts.begin(); it != facts.end(); ++ it) {
    ll fact = it->first;
    while (1) {
      int s = 0;
      for (int i = 0; i < cnt; ++ i) {
        if (a[i] % fact == 0) {
          s += 1;
        }
      }
      if (s < 2) break;
      //printf("fact: %lld\n", fact);
      //ans = ans * fib(fact) % MOD;
      ans *= fact;
      for (int i = 0; i < cnt; ++ i) {
        if (a[i] % fact == 0) {
          a[i] /= fact;
          mul[i] *= fact;
        }
      }
    }
  }

  ans = fib(ans);
  for (int i = 0; i < cnt; ++ i) {
    if (a[i] > 0) {
      ll x, y;
      gcdEx(MOD, fib( mul[i] ), &x, &y );
      while (y < 0) {
        y += MOD;
      }
      ans = ans * ( fib(a_copy[i]) * y % MOD)% MOD;
    }
  }

  printf("%lld\n", ans);

}

void solve2() {
  printf("fib:%lld\n", fib(30));
  memcpy(a_copy, a, sizeof(a));
  ll m = 1ll;
  for (int i = 0; i < cnt; ++ i) {
    m = m*fib(a[i])%MOD;
  }
  for (int i = 0; i < cnt; ++ i) {
    ll x, y;
    gcdEx(MOD, fib(a[i]), &x, &y);
    a[i] = m*y%MOD;
    while (a[i] < 0) {
      a[i] += MOD;
    }
  }
  ll g = a[0];
  for (int i = 1; i < cnt; ++ i) {
    g = gcd(g, a[i]);
  }
  ll x, y;
  gcdEx(MOD, g, &x, &y);
  printf("%lld\n", m*y%MOD);

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
    solve2();
  }

  return 0;
}

ll fib(ll n) {
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
    n >>= 1;
  }
  ll ans = (ret[0][0] * a % MOD + ret[0][1] * b % MOD) % MOD;
  return ans;
}

ll gcdEx(ll a, ll b, ll *x, ll *y) {
  if(b==0) {
    *x = 1,*y = 0;
    return a;
  } else {
    ll r = gcdEx(b, a%b, x, y);
    ll t = *x;
    *x = *y;
    *y = t - a/b * *y;
    return r;
  }
}

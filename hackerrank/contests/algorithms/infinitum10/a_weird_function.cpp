#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <map>

using namespace std;

typedef long long ll;
const ll maxn = (ll)1e7+1;
ll L, R;
ll prime[maxn];
ll p[maxn];
ll phi[maxn];
char flag[maxn];
map<ll, ll> cache;

inline
ll euler(ll n) {
  if (cache[n]) return cache[n];

  ll ret = n; 
  ll bd = (ll)sqrt(n) + 1;
  if (bd >= n) bd = n-1;
  for (ll i = 2; i <= bd; ++ i ) {
    if (n%i == 0) {
      ret *= (i-1);
      ret /= i;
      while (n%i==0) {
        n /= i;
      }
    }
  }
  if (n > 1) {
    ret *= (n-1);
    ret /= n;
  }

  cache[n] = ret;
  return ret;
}

void get_euler() {
  memset(flag, 0, sizeof(flag));
  ll idx = 0;
  for (ll i = 2; i < maxn; ++ i) {
    if (!flag[i]) {
      prime[idx++] = i;
      phi[i] = i-1;
    }
    for (ll j = 0; j < idx && i*prime[j] < maxn; ++ j) {
      flag[i*prime[j]] = 1;
      if (i%prime[j] == 0) {
        phi[i*prime[j]] = phi[i] * prime[j];
      } else {
        phi[i*prime[j]] = phi[i] * (prime[j]-1);
      }
    }
  }

  phi[1] = 1;
  p[0] = 0;

  for (ll j = 1; j < maxn; ++ j) {
    p[j] = p[j-1];
    if (j%2==0) {
      p[j] += phi[j/2]*phi[j+1];
    } else {
      p[j] += phi[j]*phi[(j+1)/2];
    }
  }

}

ll get(ll n) {
  ll low = 0, hig = maxn-1;
  while (low < hig) {
    ll mid = (low + hig) >> 1;
    if (mid*(mid+1)/2 <= n) {
      low = mid+1;
    } else {
      hig = mid-1;
    }
  }
  if (low*(low+1)/2 > n) {
    low -= 1;
  }

  return p[low];
}

void solve() {
  printf("%lld\n", get(R) - get(L-1));
}

int main() {
  int t;
  get_euler();
  scanf("%d", &t);
  for (;t--;) {
    scanf("%lld %lld", &L, &R);
    solve();
  }

  return 0;
}


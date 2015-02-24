/*
ID:atupal1
PROG:wormhole
LANG:C++11
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll maxn = 100;
ll n;
ll x[maxn];
ll y[maxn];
ll p[maxn];
ll c[maxn];
ll map[maxn][maxn];
ll vis[maxn];
ll go[maxn][maxn];

void discrete(ll *x) {
  memcpy(p, x, sizeof(p));
  sort(p, p+n);
  ll cnt = unique(p, p+n) - p;
  for (ll i = 0; i < n; ++ i) {
    for (ll j = 0; j < cnt; ++ j) {
      if (x[i] == p[j]) {
        x[i] = j;
        break;
      }
    }
  }
}

ll ans = 0;
void check() {
  for (ll i = 0; i < n; ++ i) {
    ll dx = x[i], dy  = y[i];
    ll cnt = 0;
    memset(go, 0, sizeof(go));
    while (1) {
      go[dx][dy] = 1;
      cnt += 1;
      if (cnt > n*2+2) break;
      ll idx = map[dx][dy];
      if (idx != -1) {
        dx = x[ c[idx] ];
        dy = y[ c[idx] ];
      }
      dx += 1;
      if (go[dx][dy]) {
        ans += 1;

        //for (ll i = 0; i < n; ++ i) {
        //  printf("%d -> %d\n", i, c[i]);
        //}
        //printf("\n");
        return;
      }
    }
  }
}

void conn(ll idx) {
  if (idx == n) {
    check();
    return;
  }

  if (vis[idx]) {
    conn(idx+1);
    return;
  }
  vis[idx] = 1;
  for (ll i = 0; i < n; ++ i) if (!vis[i]) {
    c[idx] = i;
    c[i] = idx;
    vis[i] = 1;
    conn(idx+1);
    vis[i] = 0;
  }
  vis[idx] = 0;
}

void solve() {
  discrete(x);
  discrete(y);

  memset(map, -1, sizeof(map));
  for (ll i = 0; i < n; ++ i) {
    map[ x[i] ][ y[i] ] = i;
  }

  memset(vis, 0, sizeof(vis));
  conn(0);

  printf("%lld\n", ans);
}

int main() {
  freopen("wormhole.in", "r", stdin);
  freopen("wormhole.out","w", stdout);
  scanf("%lld", &n);
  for (ll i = 0; i < n; ++ i) {
    scanf("%lld %lld", x+i, y+i);
  }
  solve();

  return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll maxn = (int) 1e5+10;
int n;
int c[maxn];
int pos[maxn];
int q;
int k;
ll cache[1000];

void solve() {
  if (k < 1000 && cache[k] != -1) {
    printf("%lld\n", cache[k]);
    return;
  }
  int i;
  for (i = 1; i*k <= n; ++ i) {
    c[i] = pos[i*k];
  }
  sort(c+1, c+i);

  ll ans = 0LL;
  ll cur = 1LL;
  while (cur < i) {
    ll next = cur;
    while (next+1 < i && c[next]+1 == c[next+1]) ++ next;
    ans += (next-cur+1LL)*(next-cur+1LL+1LL)/2LL;
    cur = next+1LL;
  }

  if (k < 1000) cache[k] = ans;
  printf("%lld\n", ans);
}

int main() {
  scanf("%d", &n);
  memset(cache, -1, sizeof(cache));
  for (int i = 0; i < n; ++ i) {
    int t;
    scanf("%d", &t);
    pos[t] = i;
  }
  scanf("%d", &q);
  for (int i = 0; i < q; ++ i) {
    scanf("%d", &k);
    solve();
  }

  return 0;
}


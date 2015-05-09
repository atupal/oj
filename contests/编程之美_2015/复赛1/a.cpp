#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = (int) 1e5+10;
int n, s;
int w[maxn];
int p[maxn];
int vis[maxn];
vector<int> e[maxn];

ll get(int s) {
  ll ans = w[s];
  ll max = 0;
  vis[s] =1;

  for (auto it = e[s].begin(); it != e[s].end(); ++ it) if (!vis[*it]) {
    ll tmp = get(*it);
    max += tmp;
  }

  if (0 && max && !ans) ans = max+1;
  else ans += max;

  return ans;
}

void solve() {
  memset(vis, 0, sizeof(vis));
  vis[s] = 1;
  ll max = 0;
  for (auto it = e[s].begin(); it != e[s].end(); ++ it) {
    ll tmp = get(*it);
    if (tmp > max) max = tmp;
  }

  printf("%lld\n", max);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++ cas) {
    scanf("%d %d", &n, &s);

    for (int i = 1; i <= n; ++ i) {
      e[i].clear();
    }

    for (int i = 0; i < n-1; ++ i) {
      int x, y;
      scanf("%d %d", &x, &y);
      e[x].push_back(y);
      e[y].push_back(x);
    }

    for (int i  = 0; i < n; ++ i) {
      scanf("%d", w+i+1);
    }

    printf("Case #%d: ", cas);
    solve();
  }

  return 0;
}


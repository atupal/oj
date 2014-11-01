/*
   黑书 248 页
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 10010;

int n;
int vis[maxn];
struct Cow{
  int pos;
  int val;
} s[maxn];

int cmp(Cow a, Cow b) {
  return a.val < b.val;
}

inline
int min(int a, int b) {
  return a < b ? a : b;
}

void solve() {
  scanf("%d", &n);
  memset(vis, 0, sizeof(vis));
  int m = maxn * 10;
  long long ans = 0;
  for (int i = 1; i <= n; ++ i) {
    scanf("%d", &s[i].val);
    s[i].pos = i;
    ans += s[i].val;
    if (s[i].val < m) m = s[i].val;
  }
  sort(s+1, s+n+1, cmp);

  for (int i = 1; i <= n; ++ i) {
    /*
       一个循环节
     */
    if (!vis[i]) {
      int t = maxn * 10;
      int cnt = 0;
      int x = i;
      while (!vis[x]) {
        ++ cnt;
        vis[x] = 1;
        if (s[x].val < t) t = s[x].val;
        x = s[x].pos;
      }
      ans += min((cnt-2)*t, (cnt+1)*m+t);
    }
  }
  printf("%lld\n", ans);
}

int main() {
  solve();

  return 0;
}

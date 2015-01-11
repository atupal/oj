#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 1100;

int vis[maxn];
int a[maxn];
int b[maxn];
int m, k;

void solve() {
  int cnt = 0;
  int ans = 0;
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < k; ++ i) {
    ans += a[ b[i] ];
    if (!vis[b[i]]) {
      vis[b[i]] = 1;
      cnt++;
      if (cnt == m) {
        printf("%d\n", ans);
        return;
      }
    }
  }
  printf("-1\n");
}

int main() {
  while (scanf("%d %d", &m, &k) != EOF) {
    for (int i = 1; i <= m; ++ i) {
      scanf("%d", a+i);
    }
    for (int i = 0; i < k; ++ i) {
      scanf("%d", b+i);
    }
    solve();
  }
  return 0;
}

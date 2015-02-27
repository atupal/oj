/*
ID: atupal1
PROB: sort3
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 1001;
int n;
int a[maxn];
int vis[maxn];
int cnt[4];

int getcount(int x, int y, int z) {
  int min = 0, count;
  for (int i = 0; i < cnt[1]; ++ i) {
    if (vis[i] && x) continue;
    if (a[i] == x || !x) ++ min;
  }
  count = 0;
  for (int i = cnt[1]; i < cnt[1]+cnt[2]; ++ i) {
    if (vis[i] && y) continue;
    if (a[i] == y || !y) ++ count;
  }
  if (count < min) min = count;
  count = 0; 
  for (int i = cnt[1]+cnt[2]; i < cnt[1]+cnt[2]+cnt[3]; ++ i) {
    if (vis[i] && z) continue;
    if (a[i] == z || !z) ++ count;
  }
  if (count < min) min = count;

  count = min;
  for (int i = 0; i < cnt[1] && count; ++ i) {
    if (vis[i]) continue;
    if (a[i] == x) {
      vis[i] = 1;
      count --;
    }
  }
  count = min;
  for (int i = cnt[1]; i < cnt[1]+cnt[2] && count; ++ i) {
    if (vis[i]) continue;
    if (a[i] == y) {
      vis[i] = 1;
      count --;
    }
  }
  count = min;
  for (int i = cnt[1]+cnt[2]; i < cnt[1]+cnt[2]+cnt[3] && count; ++ i) {
    if (vis[i]) continue;
    if (a[i] == z) {
      vis[i] = 1;
      count --;
    }
  }

  return min;
}

void solve() {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < n; ++ i) {
    ++ cnt[ a[i] ];
  }
  memset(vis, 0, sizeof(vis));
  int ans = getcount(1, 2, 3)*0;
  ans = getcount(0, 3, 2) + getcount(2, 1, 0) +
        getcount(3, 0, 1) + 
        getcount(2, 3, 1) * 2 + getcount(3, 1, 2) * 2;
  printf("%d\n", ans);
}

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("sort3.in", "r", stdin);
    freopen("sort3.out","w", stdout);
  }

  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", a+i);
  }
  solve();

  return 0;
}


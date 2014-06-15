/*
   线段树, 离散化
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 10010;

int n;
int l[maxn];
int r[maxn];

void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d %d", l+i, r+i);
  }
}

void solve() {
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    input();
    solve();
  }
  return 0;
}

/*
   判断某个坐标在哪个隔间里
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 5010;
int n, m;
int x1, y1, x2, y2;
int xu[maxn], xl[maxn];
int ans[maxn];

int isleft(int u, int l, int x, int y) {
  int _x1 = u - l;
  int _y1 = y1 - y2;
  int _x2 = x - l;
  int _y2 = y - y2;
  int c = _x1 * _y2 - _y1 * _x2;
  return c > 0;
}

void solve() {
  memset(ans, 0, sizeof(ans));
  for (int i = 0; i < m; ++ i) {
    int x,y;
    scanf("%d %d", &x, &y);
    int left = 0, right = n;
    while (left < right) {
      int mid = (left + right) >> 1;
      if (isleft(xu[mid], xl[mid], x, y)) {
        right = mid;
      } else {
        left = mid+1;
      }
    }
    ++ ans[left];
  }
  for (int i = 0; i <= n; ++ i) {
    printf("%d: %d\n", i, ans[i]);
  }
  printf("\n");
}

int main() {
  while (scanf("%d", &n) != EOF) {
    if (!n) return 0;
    scanf("%d %d %d %d %d", &m, &x1, &y1, &x2, &y2);
    for (int i = 0; i< n; ++ i) {
      scanf("%d %d", xu+i, xl+i);
    }
    xu[n] = x2;
    xl[n] = x2;
    solve();
  }

  return 0;
}

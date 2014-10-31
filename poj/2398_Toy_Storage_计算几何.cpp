/*
   判断某个坐标在哪个隔间里
   然后输出恰好含有 t 个坐标的隔间的个数。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 5010; int n, m;
int x1, y1, x2, y2;
int xu[maxn], xl[maxn];
int ans[maxn];
int cnt[maxn];

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
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < m; ++ i) {
    int x,y;
    scanf("%d %d", &x, &y);
    if (y > y1 || y < y2 || x < x1 || x > x2) continue;
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
    ++ cnt[ans[i]];
  }

  printf("Box\n");
  for (int i = 1; i <= m; ++ i) {
    if (cnt[i]) {
      printf("%d: %d\n", i, cnt[i]);
    }
  }
}

void qsort(int l, int r) {
  if (l >= r) return;
  int p = l;
  for (int i = l+1; i <= r; ++ i) {
    if (xu[i] < xu[l] || (xu[i] == xu[l] && xl[i] < xl[l])) {
      ++ p;
      if (xu[i] != xu[p]) xu[i] ^= xu[p] ^= xu[i] ^= xu[p];
      if (xl[i] != xl[p]) xl[i] ^= xl[p] ^= xl[i] ^= xl[p];
    }
  }
  if (xu[l] != xu[p]) xu[l] ^= xu[p] ^= xu[l] ^= xu[p];
  if (xl[l] != xl[p]) xl[l] ^= xl[p] ^= xl[l] ^= xl[p];

  qsort(l, p-1);
  qsort(p+1, r);
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
    qsort(0, n);
    solve();
  }

  return 0;
}

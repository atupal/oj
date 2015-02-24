/*
ID:atupal1
PROG:combo
LANG:C++11
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;
int a[3], b[3];

inline
int dist(int x, int y) {
  if (x < y) x ^= y ^= x ^= y;
  int l1 = x-y;
  int l2 = y+n-x;
  if (l1 < l2) return l1;
  return l2;
}

int main() {
  freopen("combo.in", "r", stdin);
  freopen("combo.out","w", stdout);
  scanf("%d", &n);
  scanf("%d %d %d", a, a+1, a+2);
  scanf("%d %d %d", b, b+1, b+2);
  int ans = 0;
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= n; ++ j) {
      for (int k = 1; k <= n; ++ k) {
        if (dist(i, a[0]) <= 2 && dist(j, a[1]) <= 2 && dist(k, a[2]) <= 2) {
          ans += 1;
          continue;
        }
        if (dist(i, b[0]) <= 2 && dist(j, b[1]) <= 2 && dist(k, b[2]) <= 2) {
          ans += 1;
        }
      }
    }
  }

  printf("%d\n", ans);

  return 0;
}


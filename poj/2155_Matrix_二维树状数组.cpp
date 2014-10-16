/*
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lowbit(x) ((x)&(-(x)))
const int maxn = 1110;
int n, t;
int bit[maxn][maxn];

void modify(int x, int y, int delta) {
  int yy = y;
  while (x <= n) {
    y = yy;
    while (y <= n) {
      bit[x][y] += delta;
      y += lowbit(y);
    }
    x += lowbit(x);
  }
}

int sum(int x, int y) {
  int ans = 0;
  int yy = y;
  while (x) {
    y = yy;
    while (y) {
      ans += bit[x][y];
      y -= lowbit(y);
    }
    x -= lowbit(x);
  }
  return ans;
}

void solve() {
  char o[55];
  memset(bit, 0 ,sizeof(bit));
  int x1, y1, x2, y2;
  for (int i = 0; i < t; ++ i) {
    scanf("%s %d %d", o, &x1, &y1);
    if (o[0] == 'C') {
      scanf("%d %d", &x2, &y2);
      modify(x1, y1, 1);
      modify(x1, y2+1, -1);
      modify(x2+1, y1, -1);
      modify(x2+1, y2+1, 1);
    } else {
      int x = sum(x1, y1);
      printf("%d\n", x&1);
    }
  }
}

int main() {
  int X;
  scanf("%d", &X);
  while (X--) {
    scanf("%d %d", &n, &t);
    solve();
    if (X) printf("\n");
  }

  return 0;
}

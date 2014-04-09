#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define maxn 1001
int T,n;
char map[maxn*8+1][maxn*8+1];
int x[maxn];
int y[maxn];

inline int Min(int a, int b) {
  return a < b ? a : b;
}

inline int Max(int a, int b) {
  return a > b ? a : b;
}

inline int abs(int a) {
  return a > 0 ? a : -a;
}

void solve() {
  long long  cnt = 0;
  for (int i = 0; i < n; ++ i) {
    for (int j = i+1; j <n ; ++ j) {
      if (x[i] != x[j] or y[i] != y[j]) {
        int x1,x2,x3,x4;
        int y1,y2,y3,y4;

        x1 = x[i] + y[j] - y[i];
        y1 = y[i] + x[i] - x[j];
        x2 = x[j] + y[j] - y[i];
        y2 = y[j] + x[i] - x[j];

        x3 = x[i] - (y[j] - y[i]);
        y3 = y[i] - (x[i] - x[j]);
        x4 = x[j] - (y[j] - y[i]);
        y4 = y[j] - (x[i] - x[j]);

        if (x1 >= 0 and y1 >= 0 and x2 >= 0 and y2 >= 0 and map[x1][y1] and map[x2][y2]) cnt ++;
        if (x3 >= 0 and y3 >= 0 and x4 >= 0 and y4 >= 0 and map[x3][y3] and map[x4][y4]) cnt ++;


      }
    }
  }

  printf("%lld\n", cnt/4);
}

int main() {
  scanf("%d", &T);
  while (T--) {
    memset(map, 0, sizeof(map));
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
      int _x,_y;
      scanf("%d %d", &_x, &_y);
      _x += 3000;
      _y += 3000;

      x[i] = _x;
      y[i] = _y;
      map[_x][_y] = 1;
    }
    solve();
  }
}

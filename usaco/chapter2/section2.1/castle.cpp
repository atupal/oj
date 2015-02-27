/*
ID: atupal1
PROB: castle
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 51;
int n, m;
int map[maxn][maxn];
int color[maxn][maxn];
int cnt;
int ccnt[maxn*maxn];
int d[256];

void dfs(int x, int y) {
  if (color[x][y] != -1) return;
  color[x][y] = cnt;
  ccnt[cnt] ++;
  if ( !(d['N'] & map[x][y]) ) {
    dfs(x-1, y);
  }
  if ( !(d['S'] & map[x][y]) ) {
    dfs(x+1, y);
  }
  if ( !(d['W'] & map[x][y]) ) {
    dfs(x, y-1);
  }
  if ( !(d['E'] & map[x][y]) ) {
    dfs(x, y+1);
  }
}

void solve() {
  memset(color, -1, sizeof(color));
  memset(ccnt, 0, sizeof(ccnt));
  cnt = 0;
  d['N'] = 2;  // up
  d['S'] = 8;  // down
  d['W'] = 1;  // left
  d['E'] = 4;  // right
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= m; ++ j) {
      if (color[i][j] == -1) {
        dfs(i, j);
        cnt ++;
      }
    }
  }

  printf("%d\n", cnt);
  int max = 0;
  for (int i = 0; i < cnt; ++ i) {
    if (ccnt[i] > max) {
      max = ccnt[i];
    }
  }
  printf("%d\n", max);

  max = 0;
  int x = -1, y = -1;
  char o = -1;
  for (int j = 1; j <= m; ++ j) {
    for (int i = n; i; -- i) {
      if ( d['N'] & map[i][j] && i-1
          && color[i][j] != color[i-1][j]
          && ccnt[ color[i][j] ] + ccnt[ color[i-1][j] ] > max) {
        max = ccnt[ color[i][j] ] + ccnt[ color[i-1][j] ];
        x = i;
        y = j;
        o = 'N';
      }
      if ( d['E'] & map[i][j] && j+1 <= m
          && color[i][j] != color[i][j+1]
          && ccnt[ color[i][j] ] + ccnt[ color[i][j+1] ] > max) {
        max = ccnt[ color[i][j] ] + ccnt[ color[i][j+1] ];
        x = i;
        y = j;
        o = 'E';
      }

    }
  }

  printf("%d\n", max);
  printf("%d %d %c\n", x, y, o);

}

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("castle.in", "r", stdin);
    freopen("castle.out","w", stdout);
  }

  scanf("%d %d", &m, &n);
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= m; ++ j) {
      scanf("%d", map[i]+j);
    }
  }
  solve();

  return 0;
}


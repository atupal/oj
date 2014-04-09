#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map[1001][101];
char f[101];

int n, k;

int DEBUG=0;

int judge(int i, int j) {
  if(DEBUG)printf("%d %d::\n", i, j);
  for (int x = 0; x < k; ++ x) {
    if(DEBUG)printf("%d:\n", x);
    if( map[i][x] == 0 && f[x] != '=' ) {if(DEBUG)printf("%d-%d-%c# ", x, map[i][x], f[x]);return 0;}
    else if (map[i][x] && map[i][x] != j) {if(DEBUG)printf("%d-%d-%c## ", x, map[i][x], f[x]);return 0;}
    else if( map[i][x] == -2 && f[x] == '=' ) {if(DEBUG)printf("%d-%d-%d### ", x, map[i][x], f[x]);return 0;}
  }
  return 1;
}

int main() {
  scanf("%d%d", &n, &k);
  memset(map, 0, sizeof(map));
  for (int x = 0; x < k; ++ x) {
    int pi;
    scanf("%d", &pi);
    int tt[1001];
    int t;
    for (int i = 0; i < pi*2; ++ i) {
      scanf("%d", &t);
      tt[i]=t-1;
    }
    char c;
    scanf("\n%c", &c);
    f[x] = c;
    for (int i = 0; i < pi; ++ i) {
      if (c=='<')
        map[tt[i]][x] = -1;
      else if (c == '=' )
        map[tt[i]][x] = -2;
      else
        map[tt[i]][x] = 1;
    }

    for (int i = pi; i < pi*2; ++ i) {
      if (c=='<')
        map[tt[i]][x] = 1;
      else if (c == '=' )
        map[tt[i]][x] = -2;
      else
        map[tt[i]][x] = -1;
    }
  }


  int ans = 0;
  for (int i = 0; i < n; ++ i) {
    if (judge(i, -1) + judge(i, 1)) {
      if (ans) {
        ans=0;
        goto here;
      }
      ans=i+1;
    }
  }

here:
  printf("%d\n", ans);

  return 0;
}

/**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define assign(x, a, b, c) direction[x][0] = a; direction[x][1] = b; direction[x][2] = c;
#define valid(x, a, b, c) (direction[x][0] + a >= 0 and \
    direction[x][0] + a < 53 and \
    direction[x][1] + b >= 0 and \
    direction[x][1] + b < 53 and \
    direction[x][2] + c >= 0 and \
    direction[x][2] + c < 30)
#define get(x, a, b, c) pos[ direction[x][0]+a ][ direction[x][1]+b ][ direction[x][2]+c ]

const int maxn = 25010;
int n;
int pos[53][53][30] = {0};
int map[maxn][3] = {-100};
int direction[256][3];

void op(int x, char ss, int i) {
  int s = (int) ss;
  if (valid(s, map[x][0], map[x][1], map[x][2]) and get(s, map[x][0], map[x][1], map[x][2]) == 0) {
    get(s, map[x][0], map[x][1], map[x][2]) = 1;
    map[i][0] = direction[s][0]+map[x][0];
    map[i][1] = direction[s][1]+map[x][1];
    map[i][2] = direction[s][2]+map[x][2];
  } else {
    //printf("%d %c: %d %d\n", x, ss, valid(s, map[x][0], map[x][1], map[x][2]), get(s, map[x][0], map[x][1], map[x][2]));
    printf("-1\n");
    exit(0);
  }
}

int num(int x) {
  int ret = 0;
  int s[] = {'L', 'R', 'F', 'B', 'O', 'U'};
  for (int i = 0; i < 6; ++ i) {
    if (valid(s[i], map[x][0], map[x][1], map[x][2]) and get(s[i], map[x][0], map[x][1], map[x][2]) == 0) {
      ret += 1;
    }
  }
  return ret;
}

void out() {
  int ans = 0;
  for (int i = 1; i <= n; ++ i) {
    ans += num(i);
  }
  printf("%d\n", ans);
}

void init() {
  assign('L', -1, 0, 0);
  assign('R', 1, 0, 0);
  assign('F', 0, 1, 0);
  assign('B', 0, -1, 0);
  assign('O', 0, 0, 1);
  assign('U', 0, 0, -1);
  pos[25][25][0] = 1;
  map[1][0] = 25;
  map[1][1] = 25;
  map[1][2] = 0;
}

void solve() {
  scanf("%d", &n);
  int x;
  char s[2];
  for (int i = 2; i <= n; ++ i) {
    scanf("%d %s", &x, s);
    op(x, s[0], i);
  }
  out();
}  

int main() {
  init();
  solve();
  return 0;
}

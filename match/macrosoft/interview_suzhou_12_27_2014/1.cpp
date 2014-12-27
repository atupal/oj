
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 210;

int n, m;
char map[maxn][maxn];
char p[10][10];
  
void rot(char x[10][10]) {
  char after_rot[10][10] = {
    {x[2][0], x[1][0], x[0][0]},
    {x[2][1], x[1][1], x[0][1]},
    {x[2][2], x[1][2], x[0][2]}
  };
  memcpy(x, after_rot, sizeof(after_rot));
}

void solve() {
  char x[10][10];
  for (int i = 1; i < n-1; ++ i) {
    for (int j = 1; j < m-1; ++ j) {
      memcpy(x, p, sizeof(p));
      for (int k = 0; k < 4; ++ k) {
        rot(x);
        int flag = 1;
        for (int n = -1; n <= 1; ++ n) {
          for (int m = -1; m <= 1; ++ m) {
            if (x[n+1][m+1] != map[i+n][j+m]) {
              flag = 0;
            }
          }
        }
        if (flag) {
          printf("%d %d\n", i+1, j+1);
          break;
        }
      }
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++ i) {
    scanf("%s", map[i]);
  }
  for (int i = 0; i < 3; ++ i) {
    scanf("%s", p[i]);
  }
  solve();

  return 0;
}

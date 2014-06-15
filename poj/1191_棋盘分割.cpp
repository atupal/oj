#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define dp(i,j,m,n,x) (mo[i][j][m][n][x] < .5 ? _dp(i,j,m,n,x) : mo[i][j][m][n][x])
#define get(x1,y1, x2,y2,  x3,y3, x4,y4,x) ((ave-sum[x1][y1][x2][y2])*(ave-sum[x1][y1][x2][y2]) + dp(x3,y3,x4,y4,x))

const int maxn = 8;

int n;
double map[maxn][maxn];
double mo[maxn][maxn][maxn][maxn][70];
double sum[maxn][maxn][maxn][maxn];
double ave;

void input() {
  ave = 0.;
  scanf("%d", &n);
  for (int i = 0; i < maxn; ++ i) {
    for (int j = 0; j < maxn; ++ j) {
      scanf("%lf", map[i]+j);
      ave += map[i][j];
    }
  }
  ave /= 1. * n;
  for (int i = 0; i < maxn; ++ i) {
    for (int j = 0; j < maxn; ++ j) {
      for (int m = i; m < maxn; ++ m) {
        for (int n = j; n < maxn; ++ n) {

          for (int x = 0; x < 70; ++ x)
            mo[i][j][m][n][x] = -1.;

          double s = .0;
          for (int x = i; x <= m; ++ x) {
            for (int y = j; y <= n; ++ y) {
              s += map[x][y];
            }
          }
          sum[i][j][m][n] = s;

        }
      }
    }
  }
}

inline
double min(double a, double b) {
  return a < b ? a : b;
}

double _dp(int x1, int y1, int x2, int y2, int x) {
  //printf("%d %d %d %d\n", x1, y1, x2, y2);
  double ans = sum[x1][y1][x2][y2] - ave;
  ans = ans * ans;
  if (x<1)
    return mo[x1][y1][x2][y2][x] = ans;
  ans = 40960000 + 100.0;
  double tmp = .0;

  for (int i = y1; i < y2; ++ i) {
    tmp = get(x1, i+1, x2,y2,  x1,y1,x2,i, x-1);
    ans = min(ans, tmp);
    tmp = get(x1,y1,x2,i, x1,i+1,x2,y2, x-1);
    ans = min(ans, tmp);
  }

  for (int i = x1; i < x2; ++ i) {
    tmp = get(i+1,y1,x2,y2,  x1,y1,i,y2, x-1);
    ans = min(ans, tmp);
    tmp = get(x1,y1,i,y2,  i+1,y1,x2,y2, x-1);
    ans = min(ans, tmp);
  }

  return mo[x1][y1][x2][y2][x] = ans;
}

void solve() {
  printf("%.3lf\n", sqrt(dp(0,0,7,7,n-1)/n));
}

int main() {
  input();
  solve();

  return 0;
}

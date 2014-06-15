#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define maxn 110

int n;
int cnt;

static struct {
  double x1;
  double y1;
  double x2;
  double y2;
}p[maxn];

double x[maxn*2];
double y[maxn*2];

int input() {
  scanf("%d", &n);
  if (not n) return 0;
  cnt = 0;
  for (int i = 0; i < n; ++ i) {
    scanf("%lf %lf %lf %lf", &p[i].x1, &p[i].y1, &p[i].x2, &p[i].y2);
    x[i*2] = p[i].x1;
    y[i*2] = p[i].y1;
    x[i*2+1] = p[i].x2;
    y[i*2+1] = p[i].y2;
  }
  return 1;
}

void solve() {
  sort(x, x + 2*n);
  sort(y, y + 2*n);
  double ans = 0;
  for (int i = 0; i < 2*n -1; ++ i) {
    for (int j = 0; j < 2*n -1; ++ j) {
      for (int k = 0; k < n; ++ k) {
        if (x[i] >= p[k].x1 and x[i+1] <= p[k].x2 and y[j] >= p[k].y1 and y[j+1] <= p[k].y2) {
          ans += (x[i+1] - x[i]) * (y[j+1] - y[j]);
          break;
        }
      }
    }
  }
  /*
     坑爹呢, 用 .2f ac, .2lf wa.!
   */
  printf("Total explored area: %.2f\n\n", ans);
}

int main() {
  int t = 0;
  while (input()) {
    printf("Test case #%d\n", ++ t);
    solve();
  }
  return 0;
}

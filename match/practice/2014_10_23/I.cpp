#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n;
#define sq(x) ((x)*(x))

void solve() {
  scanf("%d", &n);
  double ans = 0.;
  long long  t1, x1, y1;
  long long t2, x2, y2;
  x1 = t1 = y1 = 0;
  scanf("%lld %lld %lld", &t1, &x1, &y1);
  for (int i = 1; i < n; ++ i) {
    scanf("%lld %lld %lld", &t2, &x2, &y2);
    double t = sqrt(  (double)(sq(y1-y2) + sq(x1-x2))  ) / (t2-t1);
    if (t > ans) ans = t;
    t1 = t2;
    x1 = x2;
    y1 = y2;
  }
  printf("%.10lf\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}

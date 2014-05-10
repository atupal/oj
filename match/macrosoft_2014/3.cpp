#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SQ(x) ((x)*(x))

const int maxn = 110;

int N;
int x[maxn], y[maxn];

inline
int Min(int a, int b) {
  return a < b ? a : b;
}

inline
int Max(int a, int b) {
  return a > b ? a : b;
}

inline
double f(double xx) {
  double l = 0.;
  for (int i = 0; i < N; ++ i) {
    l += sqrt( SQ(xx - x[i]) + SQ(y[i]) );
  }

  return l;
}

void solve() {
  scanf("%d", &N);
  double min = 99999.;
  double max =-99999.;
  for (int i = 0; i < N; ++ i) {
    scanf("%d %d", x+i, y+i);
    min = Min(min, x[i]) * 1.;
    max = Max(max, x[i]) * 1.;
  }

  double mid, midmid;
  double lm, lmm;
  while (max - min >= 1e-7 * 5) {
    //printf("%lf %lf\n", min, max);
    mid = min + (max - min) / 3.;
    midmid = max - (max - min) / 3.;
    lm = f(mid);
    lmm = f(midmid);
    if (lm < lmm) {
      max = midmid;
    } else {
      min = mid;
    }
  }

  printf("%.6lf\n", mid);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; ++ t) {
    printf("Case %d: ", t);
    solve();
  }
}

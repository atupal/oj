#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 51000;

int n, k;

typedef long long int64;
double pos[maxn];

void solve() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i<=n ; ++i) scanf("%lf", pos+i);
  sort(pos+1, pos+n+1);
  if (n == k) {
    printf("0\n");
    return;
  }
  int l = n - k;
  double sq_sum = 0.;
  double av_sum = 0.;
  int i;
  for (i = 1; i <= l; ++ i) {
    sq_sum += pos[i]*pos[i];
    av_sum += pos[i];
  }
  double ans = sq_sum - av_sum * av_sum / l * 1.;
  for (; i <= n; ++ i) {
    sq_sum += pos[i] * pos[i] - pos[i-l] * pos[i-l];
    av_sum += pos[i] - pos[i-l];
    double tmp = sq_sum - av_sum * av_sum / l * 1.;
    if (tmp < ans) ans = tmp;
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

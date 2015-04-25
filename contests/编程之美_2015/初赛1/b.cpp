#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

const int maxn = 1010;
int N;
int x[maxn], y[maxn], w[maxn];
int l[maxn];
int r[maxn];

int cmp(int a, int b) {

  if (l[a] != l[b]) {
    return l[a] < l[b];
  }

  return r[a] < r[b];

}

void solve() {
  double ans = 0;
  for (int i = 1; i < (1<<N); ++ i) {
    int cnt = 0;
    int s[30];
    double now = 0;
    for (int j = 0; j < N; ++ j) {
      if ((i>>j)&1) {
        s[cnt++] = j;
        now += w[j];
      }
    }

    sort(s, s+cnt, cmp);
    
    now -= (double) y[ s[0] ] * y[ s[0] ];
    int mostr = s[0];
    for (int n = 1; n < cnt; ++ n) {

      if ( r[ s[n] ]  <  r[ s[n-1] ]) continue;

      now -= (double) y[ s[n] ] * y[ s[n] ];

      if ( l[ s[n] ] < r[ mostr ]) {
        double tmp = (double) (r[ mostr ] - l[ s[n] ]) / 2.0;
        now += tmp*tmp;
      }

      mostr = s[ n ];
    }
    
    //printf(" -> %.2lf\n", now);
    
    if (now > ans) {
      ans = now;
    }

  }

  printf("%.2lf\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++ i) {
    scanf("%d", &N);
    for (int j = 0; j < N; ++ j) {
      scanf("%d %d %d", x+j, y+j, w+j);
      l[j] = x[j] - y[j];
      r[j] = x[j] + y[j];
    }
    printf("Case #%d: ", i);
    solve();
  }

  return 0;
}


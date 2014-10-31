#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int maxn = 1000000;

int m, k;
int factor_cnt;
int factor[100];

int get_prime_cnt(int n) {
  int c = 1<<factor_cnt;
  int ans = 0;
  for (int i = 1; i < c; ++ i) {
    int flag = 0;
    int mul = 1;
    for (int j = 0; j < factor_cnt; ++ j) {
      if ( (i>>j) & 1 ) {
        flag ++;
        mul *= factor[j];
      }
    }
    if (flag & 1) ans += (n/mul);
    else ans -= (n/mul);
  }
  return n - ans;
}

void solve() {
  factor_cnt = 0;
  int u = (int) sqrt(m*1.0);
  int t = m;
  for (int i = 2; i <= u && t > 1; ++ i) {
    if (t % i == 0) {
      factor[factor_cnt++] = i;
      while (t%i == 0) t/= i;
    }
  }
  if (t>1) factor[factor_cnt++] = t;

  int low = 1, high = (1e9);
  while (low < high) {
    int mid = (low+high) >> 1;
    if (get_prime_cnt(mid) < k) {
      low = mid+1;
    } else {
      high = mid;
    }
  }

  printf("%d\n", high);
}

int main() {
  while (scanf("%d %d", &m, &k) != EOF) {
    solve();
  }

  return 0;
}

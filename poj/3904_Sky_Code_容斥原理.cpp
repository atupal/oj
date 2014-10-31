#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int maxn = 10000;
int n;
int prime[101];
int prime_cnt;
int count[maxn+1];
int flag[maxn+1];

long long C(int n, int r) {
  long long ret = 1;
  if (n < r) return 0;
  for (int i = 0; i < r; ++ i) {
    ret *= n-i;
  }
  for (int i = 1; i < r; ++ i) {
    ret /= i+1;
  }
  return ret;
}

void solve() {
  memset(count, 0, sizeof(count));

  for (int r = 0; r < n; ++ r) {
    int t;
    scanf("%d", &t);
    int u = (int) sqrt(t*1.);
    prime_cnt = 0;
    for (int i = 2; i <= u; ++ i) {
      if (t % i == 0) {
        prime[prime_cnt++] = i;
        while (t % i == 0) t/=i;
      }
    }
    if (t > 1) prime[prime_cnt++] = t;

    u = 1<<prime_cnt;
    for (int i = 1; i < u; ++ i) {
      int mul = 1;
      int cnt = 0;
      for (int j = 0; j < prime_cnt; ++ j) {
        if ((i>>j)&1) {
          ++ cnt;
          mul *= prime[j];
        }
      }
      ++ count[mul];
      flag[mul] = cnt;
    }

  }

  long long ans = 0;
  for (int i = 2; i <= maxn; ++ i) {
    if (count[i] < 4) continue;
    if (flag[i] & 1) {
      ans += C(count[i], 4);
    } else {
      ans -= C(count[i], 4);
    }
  }

  printf("%lld\n", C(n, 4) - ans);
}

int main() {
  while (scanf("%d", &n) != EOF) {
    solve();
  }

  return 0;
}

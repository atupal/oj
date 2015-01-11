#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 110;
const int maxm = 5e5+10;
int n, m;

typedef long long int64; 

int a[maxn][maxm];
int b[maxn][maxm];
int64 dp[maxm];
int64 pre[maxm];

inline
int min(int a, int b) {
  return a < b ? a : b;
}

inline
int max(int a, int b) {
  return a > b ? a : b;
}

void solve() {
  memset(pre, 0, sizeof(pre));
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= m; ++ j) {
      memset(&dp[j], 0x3f, sizeof(int64));
      for (int x = 1; x <= m; ++ x) {
        dp[j] = min(dp[j], pre[x]+max(0, a[i][j]-b[i-1][x]));
      }
    }
    memcpy(pre, dp, sizeof(dp));
  }
  int64 ans;
  memset(&ans, 0x3f, sizeof(int64));
  for (int x = 1; x <= m; ++ x) {
    ans = min(dp[x], ans);
  }
  printf("%lld\n", ans);
}


inline void Scan_f(int &a) {
  char c = 0;
  while(c<33)
    //c = fgetc_unlocked(stdin);
    c = getc(stdin);
  a = 0;
  while(c>33)
  {
    a = a*10 + c - '0';
    //c = fgetc_unlocked(stdin);
    c = getc(stdin);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (;t--;) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
      for (int j = 1; j <= m; ++ j) {
        //scanf("%d", a[i]+j);
        Scan_f(a[i][j]);
      }
    }

    for (int i = 1; i <= n; ++ i) {
      for (int j = 1; j <= m; ++ j) {
        //scanf("%d", b[i]+j);
        Scan_f(b[i][j]);
      }
    }
    solve();
  }

  return 0;
}

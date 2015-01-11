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
int64 min(int64 a, int64 b) {
  return a < b ? a : b;
}

inline
int64 max(int64 a, int64 b) {
  return a > b ? a : b;
}

int64 memo[maxm], ans;
int64 dfs(int i, int j, int64 sum) {
  if ( memo[(i-1)*n+m-1] != -1) return memo[i*n+m];
  if (sum >= ans) return memo[(i-1)*n+m-1] = 9223372036854775807L;
  int64 ret = 9223372036854775807L;
  for (int x = 1; x <= m; ++ x) {
    ret = min( dfs(i-1, x, sum + (int64)max(0, a[i][j]-b[i-1][x]) ), ret);
  }
  if (i == n) ans = min(ans, ret);
  return memo[(i-1)*n+m-1] = ret;
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
    //memset(memo, -1, sizeof(memo));
    //ans = 9223372036854775807L;
    //for (int i = 0; i < m; ++ i) 
    //  memo[i] = 0;
    //for (int i = 1; i <= m; ++ i)
    //  dfs(n, i, 0L);
    //printf("%lld\n", ans);
  }

  return 0;
}

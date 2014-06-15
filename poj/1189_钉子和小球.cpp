#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 100;

unsigned long long dp[maxn][maxn];
char map[maxn][maxn];
int n;
int m;

void input() {
  scanf("%d %d\n", &n, &m);
  char s;
  for (int i = 0; i < n; ++ i) {
    for (int x = 0; x < i+1; ++ x) {
      s = ' ';
      while (s != '.' and s != '*') {
        s = getchar();
      }
      map[i][x] = s;
    }
  }
}

inline
unsigned long long gcd(unsigned long long a, unsigned long long b) {
  if (a < 1) return 1;
  if (a > b) return gcd(b, a);
  unsigned long long r;
  while (a) {
    r = b % a;
    b = a;
    a = r;
  }
  return b;
}

void solve() {
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 2;
  for (int i = 0; i < n; ++ i)
    dp[0][0] *= 2;
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < i+1; ++ j) {
      if (map[i][j] == '*') {
        dp[i+1][j] += dp[i][j] / 2;
        dp[i+1][j+1] += dp[i][j] / 2;
      } else {
        int x = i+2;
        int y = j+1;
        dp[x][y] += dp[i][j];
      }
    }
  }
  unsigned long long t = gcd(dp[0][0], dp[n][m]);
  if (dp[n][m] == 0) 
    dp[0][0] = 1;
  printf("%lld/%lld\n", dp[n][m]/t, dp[0][0]/t);
}

int main() {
  input();
  solve();

  return 0;
}

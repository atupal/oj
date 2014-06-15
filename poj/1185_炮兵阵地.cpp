#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 110;

int n;
int m;
int map[maxn];

int num;
int dp[2][61][61];
int state[61];
int cnt[61];
int w[61][61][61];

int vis[maxn];
int s[maxn];

void input() {
  scanf("%d %d", &n, &m);
  getchar();
  for (int i = 0; i < n; ++ i) {
    int tmp = 0;
    for (int j = 0; j < m; ++ j) {
      char a = getchar();
      if (a != 'P') {
        tmp = tmp * 2 + 1;
      } else {
        tmp = tmp * 2;
      }
    }
    getchar();
    map[i] = tmp;
  }

  memset(cnt, 0, sizeof(cnt));
  memset(vis, 0, sizeof(vis));
  memset(s, 0, sizeof(s));
  s[0] = 0;
  cnt[0] = 0;
  num = 1;
}

inline
int Max(int a, int b) {
  return a > b ? a : b;
}

int deeps = 0;
void dfs(int ind) {
  if (ind >= m) {
    int tmp = 0;
    for (int i = 0; i < m; ++ i) {
      //printf("%d", s[i]);
      tmp = tmp * 2 + s[i];
    }
    state[num++] = tmp;
    cnt[num-1] = deeps;
    //printf(" :%d, %d\n",tmp, deeps);
    return;
  }
  ++ deeps;
  s[ind] = 1;

  for (int i = ind+3; i < m; ++ i) {
    //可以放完后不放了，所以可以达到 m+1
    dfs(i);
  }
  dfs(m+1);

  s[ind] = 0;
  -- deeps;
}

void solve() {
  for (int i = 0; i < m; ++ i) {
    dfs(i);
  }
  //printf("%d\n", num);
  for (int i = 0; i < num; ++ i) {
    for (int j = 0; j < num; ++ j) {
      for (int k = 0; k < num; ++ k) {
        w[i][j][k] = 1;
        for (int x = 0; x < m; ++ x) {
          int mask = 1 << x;
          if ( (not not(mask & state[i]) + not not(mask & state[j]) + not not(mask & state[k]) ) > 1) {
            w[i][j][k] = 0;
            break;
          }
        }
      }
    }
  }

  int ans = 0;
  int pre = 0;
  int now = 1;
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < n; ++ i) {
    //memset(dp[now], 0, sizeof(dp[now]));  不需要 因为 dp的值是递增的
    for (int j = 0; j < num; ++ j) {
      if (not (map[i] & state[j])) {
        for (int k = 0; k < num; ++ k) {
          if (w[0][k][j]) {
            for (int l = 0; l < num; ++ l) {
              if (w[l][k][j]) {
                dp[now][j][k] = Max(dp[now][j][k], dp[pre][k][l] + cnt[j]);
                ans = Max(ans, dp[now][j][k]);
              }
            }
          }
        }
      }
    }
    now = not now;
    pre = not pre;
  }

  printf("%d\n", ans);
}

int main() {
  input();
  solve();

  return 0;
}

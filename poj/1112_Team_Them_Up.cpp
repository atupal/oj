#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 101;

int N;
int map[maxn][maxn];
int col[maxn];
int rmap[maxn][maxn];
int _0or1[maxn];
int pre[maxn][maxn*2];
int cnt[2][maxn];

int DP[maxn][maxn*2];

inline 
int Max(int a, int b) {
  return a > b ? a : b;
}

void init() {
  N = 0;
  memset(map, 0, sizeof(map));
  memset(pre, -1, sizeof(pre));
  memset(_0or1, -1, sizeof(_0or1));
  memset(col, -1, sizeof(col));
  memset(rmap, -1, sizeof(rmap));
  memset(DP, -1, sizeof(DP));
}

void input() {
  scanf("%d", &N);

  int t;
  for (int i = 0; i < N; ++ i) {
    while (1) {
      scanf("%d", &t);
      if (!t) 
        break;
      map[i][t-1] = 1;
    }
  }
}

void dfs(int ind, int color, int _01) {
  col[ind] = color;
  _0or1[ind] = _01;

  for (int i = 0; i < N; ++ i) {

    if (col[i] == -1 and rmap[ind][i]) {
      dfs(i, color, not _01);
    }
  }
}

int color = 0;
int inf_gra() {
  for (int i = 0; i < N; ++ i) {
    rmap[i][i] = 0;
  }
  for (int i = 0; i < N; ++ i) {
    for (int j = 0; j < N; ++ j) {
      if (map[i][j] and map[j][i]) {
        rmap[i][j] = 0;
        rmap[j][i] = 0;
      }
    }
  }

  for (int i = 0; i < N; ++ i) {
    if (col[i] == -1) {
      dfs(i, ++color-1, 0);

      for (int p = 0; p < N; ++ p) {
        for (int q = 0; q < N; ++ q) {
          if (col[p] == col[q] and col[p] == color-1) {
            if (rmap[p][q] and _0or1[p] == _0or1[q]) {
              printf("No solution\n");
              exit(0);
            }
          }
        }
      }
    }
  }

  //for (int i = 0; i < N; ++ i) 
    //printf("%d:%d %d\n", i+1, col[i], _0or1[i]);
  
  for (int i = 0; i < color; ++ i) {
    cnt[0][i] = 0;
    cnt[1][i] = 0;
    for (int x = 0; x < N; ++ x) {
      if (col[x] == i) {
        if (_0or1[x] == 0) {
          ++ cnt[0][i];
        } else {
          ++ cnt[1][i];
        }
      }
    }
  }

  return color;
}

//dp[i][j]表示第i个连通分量达到j的差值，true为可达，false为不可达。
void dp() {
  memset(DP[0], 0, sizeof(int) * maxn * 2 * maxn);
  DP[0][cnt[0][0] - cnt[1][0] + maxn] = 1;
  DP[0][cnt[1][0] - cnt[0][0] + maxn] = 2;
  for (int i = 0; i < color - 1; ++ i) {
    for (int j = -100; j <= 100; ++ j) {
      if (DP[i][j + maxn]) {
        int tmp;
        tmp = j + cnt[0][i+1] - cnt[1][i+1];
        if (tmp <= 100 and tmp >= -100) {
          DP[i+1][tmp + maxn] = 1;
          pre[i+1][tmp + maxn] = j;
        }
        tmp = j + cnt[1][i+1] - cnt[0][i+1];
        if (tmp <= 100 and tmp >= -100) {
          DP[i+1][tmp + maxn] = 2;
          pre[i+1][tmp + maxn] = j;
        }
      }
    }
  }
}

inline
int Abs(int a) {
  return a < 0 ? -a : a;
}

void out() {
  int ans = 100000;
  for (int i = -100; i <= 100; ++ i) {
    if (DP[color-1][i+maxn] and Abs(i) < Abs(ans)) {
      ans = i;
    }
  }

  //printf("ans:%d\n", ans);

  int t1[maxn];
  int cnt_t1 = 0;
  memset(t1, 0, sizeof(t1));
  int x = ans + maxn;
  for (int k = color-1; k >= 0; --k ) {
    //printf("color %d, %d:%d\n", k, pre[k][x], DP[k][x]);
    for (int i = 0; i < N; ++ i) {
      if (col[i] == k and _0or1[i] == DP[k][x]-1) {
        t1[i] = 1;
        ++ cnt_t1;
      }
    }
    x = pre[k][x] + maxn;
  }
  printf("%d ", cnt_t1);
  for (int i = 0; i < N; ++ i) if (t1[i]) {
    printf("%d ", i+1);
  }
  printf("\n");

  printf("%d ", N - cnt_t1);
  for (int i = 0; i < N; ++ i) if (not t1[i]) {
    printf("%d ", i+1);
  }
  printf("\n");
}

void solve() {
  color = inf_gra();
  dp();
  out();
}

int main () {
  init();
  input();
  solve();

  return 0;
}

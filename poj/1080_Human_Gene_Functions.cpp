#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 102
char a[maxn];
char b[maxn];
int n;
int m;
int dp[maxn][maxn][maxn];


/* 
 * dp(i, j, x) 表示 串 ai-an 与 串 bj-bm bj连接ax时的最大得分，x=maxn-1时表示bj连接空格:)
 * wa 了好多次， 动态规划还是需要细心啊，然后 以后 别再用什么 i，j，x 什么的 当 函数形参了
 * 一不小心就在 循环里 写个 ++i 之类的，然后尽量模块化，不要复制粘贴代码块，然后改几个小地方。
 * */


int score[5][5] = {
  {5, -1, -2, -1, -3},
  {-1, 5, -3, -2, -4},
  {-2, -3, 5, -2, -2},
  {-1, -2, -2, 5, -1},
  {-3, -4, -2, -1, -1000}
};


int get(int i, int j, int x) {
  if (dp[i][j][x] != -1) return dp[i][j][x];

  if (x == maxn - 1) {
    int max = 0;
    for (int p = j; p < m; ++ p) {
      max += score[(int)b[p]][4];
    }
    for (int p = i; p < n; ++ p) {
      max += score[ (int)a[p] ][4];
    }
    //max += score[ (int)b[j] ][4];
 
    for (int p = i; p < n; ++ p) if(j +1 < m){
      int tmp = get(i, j + 1, p) + score[ (int)b[j] ][4];
      max = tmp > max ? tmp : max;
    }

    if (j + 1 < m) {
      int tmp = get(i, j + 1, maxn - 1) +  score[ (int)b[j] ][4];
      max = tmp > max ? tmp : max;
    }

    return dp[i][j][x] = max;
  }

  int max = 0;
  for (int p = j +1; p < m; ++ p) {
    max += score[(int)b[p]][4];
  }
  for (int p = x + 1; p < n; ++ p) {
    max += score[ (int)a[p] ][4];
  }

  int base = 0;
  for (int p = i; p < x; ++ p) {
    base += score[(int)a[p]][4];
  }
  base += score[(int)a[x]][(int)b[j]];
  max += base;

  for (int p = x + 1; p < n; ++ p) if (j+1 < m) {
    int tmp = base + get(x+1, j+1, p);
    if (tmp > max) {
      max = tmp;
    }
  }

  if (j + 1 < m and x + 1 < n) {
    //int tmp = get(x, j + 1, maxn - 1) +  score[ (int)b[j] ][4];
    int tmp = get(x + 1, j + 1, maxn - 1) +  base;
    max = tmp > max ? tmp : max;
  }

  //printf("%d %d %d: %d\n", i, j, x, max);
  return dp[i][j][x] = max;
}

void init() {
  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < n; ++ i) {
    switch (a[i]) {
      case 'A': a[i] = 0; break;
      case 'C': a[i] = 1; break;
      case 'G': a[i] = 2; break;
      case 'T': a[i] = 3; break;
    }
  }

  for (int i = 0; i < m; ++ i) {
    switch (b[i]) {
      case 'A': b[i] = 0; break;
      case 'C': b[i] = 1; break;
      case 'G': b[i] = 2; break;
      case 'T': b[i] = 3; break;
    }
  }

}

void solve(){
  int ans = -maxn * maxn;
  for (int i = 0; i < n; ++ i) {
    int tmp = get(0, 0, i);
    ans = tmp > ans ? tmp : ans;
  }
  int tmp = get(0, 0, maxn - 1);// +  score[ (int)b[0] ][4];
  ans = tmp > ans ? tmp : ans;
  printf("%d\n", ans);
}

int main(void) {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %s", &n, a);
    scanf("%d %s", &m, b);
    if (m > n) {
      m ^= n ^= m ^= n;
      char t[maxn];
      strcpy(t, a);
      strcpy(a, b);
      strcpy(b, t);
    }
    init();
    solve();
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dp(i, j) (momo[i][j] != -1 ? momo[i][j] : _dp(i, j))

const int maxn = 601;

int V, P;

int s[maxn];
int momo[maxn][maxn];
int m[maxn][maxn];
int pre[maxn][maxn];

void input() {
  scanf("%d %d", &V, &P);
  for (int i = 0; i < V; ++ i) {
    scanf("%d", s+i);
  }

  memset(momo, -1, sizeof(momo));
  memset(m, 0, sizeof(m));
  memset(pre, -1, sizeof(pre));

  /*预处理
  for (int i = 0; i < V; ++ i) {
    for (int j = i; j < V; ++ j) {

      int tmp = 0;
      int x = (i+j)>>1;
      for (int k = i; k <= x; ++ k) {
        tmp += s[x] - s[k];
      }
      for (int k = x+1; k <= j; ++ k) {
        tmp += s[k] - s[x];
      }
      m[i][j] = tmp;
    }
  }
  */

  for(int i = 0 ; i <= V ; i ++) //这里有一个递推公式可以进行预处理
  {   m[i][i] = 0;
    for(int j = i + 1 ; j < V ; j ++) m[i][j] = m[i][j - 1] + s[j] - s[(j + i)/2];
  }

  for (int i = 0; i < V; ++ i) {
    momo[i][i] = 0;
    pre[i][i] = i;
    momo[i][0] = m[0][i];
    pre[i][0] = 0;
  }

  // 使用递推的版本
  for (int i = 1; i < V; ++ i) {
    for (int j = 1; j <= i; ++ j) {
      int min = maxn * 10000;
      for (int x = pre[i-1][j-1]; x < i; ++ x) {
        int tmp = momo[x][j-1] + m[x+1][i];
        if (tmp < min) {
          min = tmp;
          pre[i][j] = x;
        }
      }
      momo[i][j] = min;
    }
  }

}

// 前 i 个村庄建立第 j 个邮局的最小距离和, 下标均从 0 开始
// 使用 pre 的是符合四边形优化的，虽然我也不知道是怎么搞得.
int _dp(int i, int j) {
  int min = maxn * 10000;
  int tmp;

  //for (int x = j-1; x < i; ++ x) {
  dp(i-1,j-1);
  for (int x = pre[i-1][j-1]; x < i; ++ x) {
    tmp = dp(x, j-1) + m[x+1][i];

    if (tmp < min) {
      min = tmp;
      pre[i][j] = x;
    }
  }

  return momo[i][j] = min;
}

void solve() {
  //int ans = dp(V-1, P-1);
  //printf("%d\n", ans);
  printf("%d\n", momo[V-1][P-1]);
}

int main() {
  input();
  solve();

  return 0;
}

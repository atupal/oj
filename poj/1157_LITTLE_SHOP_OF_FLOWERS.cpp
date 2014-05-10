#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dp(i, j) (momo[i][j] != -1 ? momo[i][j] : _dp(i, j))

const int maxn = 101;

int F, V;
int A[maxn][maxn];
int momo[maxn][maxn];

void input() {
  scanf("%d %d", &F, &V);
  for (int i = 0; i < F; ++ i) {
    for (int j = 0; j < V; ++ j) {
      scanf("%d", A[i]+j);
    }
  }

  memset(momo, -1 ,sizeof(momo));

  momo[0][0] = A[0][0];
  for (int i = 1; i < F; ++ i) {
    momo[i][i] = momo[i-1][i-1] + A[i][i];
    for (int j = 0; j < i; ++ j) {
      momo[i][j] = -50 * maxn;
    }
  }

}

// 前 i 朵花放在前 j 个花瓶里最大的观赏度
int _dp(int i, int j) {
  int max = -50 * maxn;
  int tmp = 0;

  for (int x = i; x <= j; ++ x) {
    tmp = dp(i-1, x-1) + A[i][x];
    if (tmp > max) {
      max = tmp;
    }
  }

  return momo[i][j] = max;
}

void solve() {
  int ans = dp(F-1, V-1);
  printf("%d\n", ans);
}

int main() {
  input();
  solve();

  return 0;
}

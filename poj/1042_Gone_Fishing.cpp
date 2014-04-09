#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, h, f[26], d[26] ,t[25];
int dp[26][16 * 12 + 10];
int pre[26][16 * 12 + 10];

inline int Max(int a, int b) {
  return a > b ? a : b;
}

void print(int i, int out) {
  if (i<0)return;
  print(i-1, pre[i][out]);
  if (i)printf(", %d", (out-pre[i][out]-t[i]) * 5);
  else printf("%d", (out-pre[i][out]-t[i]) * 5);
}

void solve() {
  memset(dp, -1, sizeof(dp));
  memset(pre, 0, sizeof(pre));
  int max=0;
  int max_n = 0;
  //for (int i = 1; f[0] - (i-1)*d[0] > 0 && i <= h ; ++ i) {
  dp[0][0]=0;
  for (int i = 1; i <= h ; ++ i) {
    dp[0][i] = dp[0][i-1] + Max(0, f[0] - (i-1) * d[0]);
    if (dp[0][i] >= max) {
      max=dp[0][i];
      max_n = 0;
    }
  }


  for (int i = 1; i < n; ++ i) {
    for (int j = t[i]; j <= h; ++ j) {
      //for (int x = 0; x <= j-t[i] && f[i] - (x-1) * d[i] > 0; ++ x) {
      //if (dp[i-1][j-t[i]] == -1) continue;
      dp[i][j] = dp[i-1][j-t[i]];  // 初始化 ！！ 不然动归中会出现 负负得正的情况！
      pre[i][j] = j-t[i];   // 一定要初始化  ！！ 不然输出的时间会不对
      for (int x = 1; x <= j-t[i]; ++ x) {
        if (j-x-t[i]>=0 and dp[i-1][j-x-t[i]]!=-1) {
          int tmp = dp[i-1][j-x-t[i]] +Max(0,  (f[i]-(x-1)*d[i]+f[i])*x/2  );
          if (tmp > dp[i][j]) {
            dp[i][j] = tmp;
            pre[i][j] = j-x-t[i];
            if (pre[i][j] < 0) printf("error:%d\n", pre[i][j]);
            if (tmp > max) {
              max=tmp;
              max_n = i;
            }
          }
        }
      }
    }
  }

  /*
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j <= h; ++ j) {
      printf("%d\t", dp[i][j]);
    }
    printf("\n");
  }
  */

  print(max_n, h);
  for (int i = max_n + 1; i < n; ++ i)
    printf(", %d", 0);
  printf("\n");

  printf("Number of fish expected: %d \n\n", max);

}

int main() {
  while ( scanf("%d", &n) , n ) {
    scanf("%d", &h);
    h *= 12;
    for (int i = 0; i < n; ++ i) scanf("%d", &f[i]);
    for (int i = 0; i < n; ++ i) scanf("%d", &d[i]);
    for (int i = 1; i < n; ++ i) scanf("%d", &t[i]);
    solve();
  }
}

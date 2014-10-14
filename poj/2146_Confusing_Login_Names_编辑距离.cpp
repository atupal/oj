/*
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 210;
int n, d;
char *s[maxn];
int dp[21][21];

int cmp(int a, int b) {
  int i;
  for (i = 0; s[a][i] && s[b][i]; ++ i) {
    if (s[a][i] != s[b][i]) {
      return s[a][i] < s[b][i];
    }
  }
  return s[a][i] < s[b][i];
}

void qsort(int l, int r) {
  if (l >= r) return;
  int p = l;
  char *t;
  for (int i = l+1; i <= r; ++ i) {
    if (cmp(i, l)) {
      ++ p;
      t = s[p], s[p] = s[i], s[i] = t;
    }
  }
  t = s[p], s[p] = s[l], s[l] = t;
  qsort(l, p-1);
  qsort(p+1, r);
}

int input() {
  if (scanf("%d", &n) == EOF) return 0;
  if (!n) return 0;
  scanf("%d", &d);
  for (int i = 0; i < n; ++ i) {
    s[i] = (char *) malloc (sizeof(char)*20);
    scanf("%s", s[i]);
  }
  return 1;
}

inline
int min(int a, int b) {
  return a < b ? a : b;
}

int get(char *a, char *b) {
  int i, j;
  int da[maxn], db;
  memset(da, 0, sizeof(da));
  for (i = 1; a[i-1]; ++ i) {
    for (j = 1; b[j-1]; ++ j) {
      dp[i][j] = maxn;
      dp[0][j] = j;
    }
    dp[i][0] = i;
  }
  dp[0][0] = 0;

  for (i = 1; a[i-1]; ++ i) {
    db = 0;
    for (j = 1; b[j-1]; ++ j) {
      dp[i][j] = dp[i-1][j-1] + (a[i-1]!=b[j-1]); // 替换
      dp[i][j] = min(dp[i][j], min(dp[i-1][j], dp[i][j-1]) + 1); // 插入或删除
      int i1 = da[(int)b[j-1]];
      int j1 = db;
      if (a[i-1] == b[j-1]) {
        db = j;
      }
      if (i1 && j1) {
        dp[i][j] = min(dp[i][j], dp[i1-1][j1-1] + (i-i1-1) + (j-j1-1) + 1);
        // 交换,并在交换的字母之间可能插入或删除
        // i1 是 b 串末端的字母在 i 之前的位置, (i-i1-1) 就是 a 删除的字符数
        // j1 是 a 串末端的字母在 j 之前的位置. (j-j1-1) 就是 a 插入的字符数
      }
    }
    da[(int)a[i-1]] = i;
  }

  //for (i = 1; a[i-1]; ++ i) {
    //for (j = 1; b[j-1]; ++ j) {
      //printf("%d ", dp[i][j]);
    //}
    //printf("\n");
  //}
  //printf("\n");

  //return dp[i-1][j-1];
  if (dp[i-1][j-1] <= d) return dp[i-1][j-1]+1;
  return 0;
}

void solve() {
  qsort(0, n-1);

  int cnt = 0;
  for (int i = 0; i < n-1; ++ i) {
    for (int j = i+1; j < n; ++ j) {
      int flag = get(s[i], s[j]);
      if (flag) {
        printf("%s,%s\n", s[i], s[j]);
        ++ cnt;
      }
    }
  }
  printf("%d\n", cnt);
}

int main() {
  while (input()) {
    solve();
  }

  return 0;
}

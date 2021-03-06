#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 10010;

int n;
int width;
char s[maxn];
int len[maxn];
int allcnt;

int dp[maxn];
int ans[maxn];

inline
int solve(int x) {
  if (x >= n) return 0;
  if (dp[x] != -1) return dp[x];
  int min = 0;
  int l = len[x];
  if (l < width) {
    min += 500;
  }
  min += solve(x+1);
  ans[x] = x;

  for (int i = x + 1; i < n; ++ i) {
    l += len[i] + 1;
    if (l <= width) {
      int m = (width - l) % (i - x);
      int nn = (width - l) / (i - x);
      int score = m * ( (nn+1) * (nn+1) ) + (i - x - m) * (nn * nn); 
      score += solve(i+1); 
      if (score <= min) {
        min = score;
        ans[x] = i;
      }
    } else {
      break;
    }
  }

  return dp[x] = min;
}

void out(int x, int l) {
  if (x >= n) {
    return;
  }
  int sum = 0;
  for (int i = x; i <= ans[x]; ++ i) 
    sum += len[i];

  int m = ans[x] - x == 0 ? 0 : (width - sum) % (ans[x] - x);
  int nn = ans[x] - x == 0 ? 0 : (width - sum) / (ans[x] - x);

  int bs = 0;
  int cnt = 0;
  for (int i = x; i <= ans[x]; ++ i) {
    for (int j = cnt; j < cnt + len[i]; ++ j) {
      printf("%c", s[l + j]);
    }
    ++ bs;
    if (bs <= ans[x] - x  - m) {
      for (int k = 0; k < nn; ++ k) if (i != ans[x])
        printf(" ");
        //printf("\033[31m+\033[0m");
    } else {
      for (int k = 0; k <= nn; ++ k)  if (i != ans[x])
        printf(" ");
        //printf("\033[31m+\033[0m");
    }
    cnt += len[i];
  }

  printf("\n");
  out(ans[x] + 1, l + sum);
}

int main() {
  width = -1; // init 
  while (1) {
    if (width != -1) {
      printf("\n");
    }
    scanf("%d", &width);
    if (!width) {
      break;
    }
    getchar();
    n = 0;
    allcnt = -1;
    memset(dp, -1, sizeof(dp));
    memset(ans, 0, sizeof(ans));
    char a;
    int cnt = 0;
    while (1) {
      a = getchar();
      if (a == '\n') {
        if (cnt > 0) {
          len[n] = cnt;
          cnt = 0;
          ++ n;
        }
        if ((a = getchar()) == '\n') {
          break;
        } else {
          ++ cnt;
          s[++allcnt] = a;
        }
      } else if (a != ' '){
        ++ cnt;
        s[++allcnt] = a;
      } else if(cnt > 0){
        len[n] = cnt;
        cnt = 0;
        ++ n;
      }
    }
    s[++allcnt] = '\0';
    solve(0);
    //int score = solve(0);
    //printf("%d\n", score);
    //printf("%s\n", s);
    out(0, 0);
  }

  return 0;
}

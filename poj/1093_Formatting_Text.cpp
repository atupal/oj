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
int Min(int a, int b) {
  return a < b ? a : b;
}

inline
int solve(int x) {
  if (x < 0) return 0;
  if (dp[x] != -1) return dp[x];
  int min = 0;
  int l = len[x];
  if (l < width) {
    min += 500;
  }
  min += solve(x-1);
  ans[x] = x;

  for (int i = x - 1; i >= 0; -- i) {
    l += len[i] + 1;
    if (l <= width) {
      int m = (width - l) % (x - i);
      int n = (width - l) / (x - i);
      int score = m * ( (n+1) * (n+1) ) + (x - i - m) * (n * n); 
      score += solve(i-1); 
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
  if (x < 0) {
    return;
  }
  int sum = 0;
  for (int i = ans[x]; i <= x; ++ i) 
    sum += len[i];

  out(ans[x] - 1, l - sum);
  int m = x - ans[x] == 0 ? 0 : (width - sum) % (x - ans[x]);
  int nn = x - ans[x] == 0 ? 0 : (width - sum) / (x - ans[x]);

  int cnt = 0;
  int bs = 0;
  for (int i = ans[x]; i <= x; ++ i) {
    for (int j = cnt; j < cnt + len[i]; ++ j) {
      printf("%c", s[l-sum + +j]);
    }
    ++ bs;
    if (bs <= x - ans[x] - m) {
      for (int k = 0; k < nn; ++ k) if (i != x)
        printf(" ");
        //printf("\033[31m+\033[0m");
    } else {
      for (int k = 0; k <= nn; ++ k)  if (i != x)
        printf(" ");
        //printf("\033[31m+\033[0m");
    }
    //printf(" ");
    cnt += len[i];
  }

  if (nn == 0 and m == 0) {
    for (int i = 0; i < width - len[x]; ++ i) {
      //printf(" ");
    }
  }

  if (x != n-1) {
    printf("\n");
  }
}

int main() {
  width = -1; // init 
  while (1) {
    int flag = 0;
    if (width != -1) {
      flag = 1;
      printf("\n\n");
    }
    scanf("%d", &width);
    if (!width) {
      break;
    } else if(flag){
      //printf("\n\n");
    }
    getchar();
    n = 0;
    allcnt = -1;
    memset(dp, -1, sizeof(dp));
    //dp[0] = 0;
    memset(ans, 0, sizeof(ans));
    char a;
    int cnt = 0;
    while (1) {
      a = getchar();
      if (a == '\n') {
        len[n] = cnt;
        cnt = 0;
        ++ n;
        if ((a = getchar()) == '\n') {
          break;
        } else {
          ++ cnt;
          s[++allcnt] = a;
        }
      } else if (a != ' '){
        ++ cnt;
        s[++allcnt] = a;
      } else {
        len[n] = cnt;
        cnt = 0;
        ++ n;
      }
    }
    s[++allcnt] = '\0';
    solve(n);
    //int score = solve(n);
    //printf("%d\n", score);
    //printf("%s\n", s);
    out(n-1, allcnt);
  }

  return 0;
}

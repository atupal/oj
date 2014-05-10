#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dp(i, j) (momo[i][j] != -1 ? momo[i][j] : _dp(i, j))

const int maxn = 101;

int momo[maxn][maxn];
int choice[maxn][maxn];
int path[maxn][maxn];

char bs[maxn];
int val[257];
char rev[257];

void input() {
  scanf("%s", bs);
  memset(momo, -1, sizeof(momo));
  memset(val, 0, sizeof(val));
  val['('] = -1;
  val[')'] = 1;
  val['['] = -2;
  val[']'] = 2;
  rev['('] = ')';
  rev[')'] = '(';
  rev['['] = ']';
  rev[']'] = '[';


  for (int i = 0; i < maxn; ++ i) {
    momo[i][i] = 2;
    if (val[(int)bs[i]] < 0) {
      choice[i][i] = 1;
    } else {
      choice[i][i] = 2;
    }
    path[i][i] = i;
    for (int j = 0; j < i; ++ j) {
      momo[i][j] = 0;
    }
  }
}

inline
int _dp(int i, int j) {
  int min = maxn * maxn;
  int tmp;
  for (int x = i+1; x <= j; ++ x) {
    if (val[(int)bs[i]] < 0 and val[(int)bs[i]] + val[(int)bs[x]] == 0) {
      tmp = dp(i+1, x-1) + dp(x+1, j) + 2;
      if (tmp < min) {
        min = tmp;
        choice[i][j] = 0;
        path[i][j] = x;
      }
    }
  }

  if (val[(int)bs[i]] < 0) {
    for (int x = i; x <= j; ++ x) {
      tmp = dp(i+1, x) + dp(x+1, j) + 2;
      if (tmp < min) {
        min = tmp;
        choice[i][j] = 1;
        path[i][j] = x;
      }
    }
  } else {
      tmp = dp(i+1, j) + 2;
      if (tmp < min) {
        min = tmp;
        choice[i][j] = 2;
        path[i][j] = i+1;
      }
  }

  return momo[i][j] = min;
}

void solve() {
  int ans;
  ans = dp(0, strlen(bs)-1);
  //printf("ans: %d\n", ans);
}

void output(int i, int j) {
  if (j < i) return;
  if (choice[i][j] == 0) {
    printf("%c", bs[i]);
    output(i+1, path[i][j] - 1);
    printf("%c", bs[path[i][j]]);
    output(path[i][j] + 1, j);
  } else if (choice[i][j] == 1){
    printf("%c", bs[i]);
    output(i+1, path[i][j]);
    printf("%c", rev[(int)bs[i]]);
    output(path[i][j] + 1, j);
  } else {
    printf("%c%c", rev[(int)bs[i]], bs[i]);
    output(i+1, j);
  }
}

int main() {
  input();
  solve();
  output(0, strlen(bs)-1);
  printf("\n");

  return 0;
}

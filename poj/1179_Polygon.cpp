#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
  
#define dp(i, j) (mo[i][j] != minn ? mo[i][j] : _dp(i,j))
#define dp_min(i, j) (mo_min[i][j] != -minn ? mo_min[i][j] : _dp_min(i,j))

const int maxn = 51;
const int minn = -32767000;

int n;
char e[maxn];
int v[maxn];
int mo[maxn][maxn];
int mo_min[maxn][maxn];

void input() {
  scanf("%d", &n);
  char s[2];
  for (int i =0; i < n; ++ i) {
    scanf("%s %d", s, v+i);
    e[i] = s[0];
  }

  //memset(mo, 1, sizeof(mo));
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < n; ++ j) {
      mo[i][j] = minn;
      mo_min[i][j] = -minn;
    }
  }

  for (int i = 0; i < n; ++ i) {
    mo[i][i] = v[i];
    mo_min[i][i] = v[i];
  }
}

inline
int Min(int a, int b) {
  return a < b ? a : b;
}

inline
int Max(int a, int b) {
  return a > b ? a : b;
}


int _dp_min(int ,int);

inline
int _dp(int i, int j) {
  int max = minn;
  if (j < i) {
    j += n;
  }

  int tmp;
  for (int x = i; x < j; ++ x) {
    int xx = x % n;
    if (e[(x+1)%n] == 't') {
      tmp = dp(i, xx) + dp((xx + 1)%n, j%n);
      max = Max(max, tmp);
    } else {
      tmp = dp(i, xx) * dp((xx + 1)%n, j%n);
      max = Max(max, tmp);
      tmp = dp_min(i, xx) * dp_min((xx + 1)%n, j%n);
      max = Max(max, tmp);
      tmp = dp(i, xx) * dp_min((xx + 1)%n, j%n);
      max = Max(max, tmp);
      tmp = dp_min(i, xx) * dp((xx + 1)%n, j%n);
      max = Max(max, tmp);
    }
  }

  return mo[i][j%n] = max;
}

inline
int _dp_min(int i, int j) {
  int min = -minn;
  if (j < i) {
    j += n;
  }

  int tmp;
  for (int x = i; x < j; ++ x) {
    int xx = x % n;
    if (e[(x+1)%n] == 't') {
      tmp = dp_min(i, xx) + dp_min((xx + 1)%n, j%n);
      min = Min(min, tmp);
    } else {
      tmp = dp(i, xx) * dp((xx + 1)%n, j%n);
      min = Min(min, tmp);
      tmp = dp_min(i, xx) * dp_min((xx + 1)%n, j%n);
      min = Min(min, tmp);
      tmp = dp(i, xx) * dp_min((xx + 1)%n, j%n);
      min = Min(min, tmp);
      tmp = dp_min(i, xx) * dp((xx + 1)%n, j%n);
      min = Min(min, tmp);
    }
  }

  return mo_min[i][j%n] = min;
}

void solve() {
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < n; ++ j) {
      dp(i, j);
      //mo[i][j] = dp(i, j);
    }
  }

  int ans = minn;
  for (int i = 0; i < n; ++ i) {
    if (mo[i][(i+n-1)%n] > ans) {
      ans = mo[i][(i+n-1)%n];
    }
    //printf("%d\n", mo[i][(i+n-1)%n]);
  }
  printf("%d", ans);
  int flag = 0;
  for (int i = 0; i < n; ++ i) {
    if (mo[i][(i+n-1)%n] == ans) {
      if (not flag) {
        printf("\n%d", i+1);
        flag = 1;
      }
      else {
        printf(" %d", i+1);
      }
    }
  }
  printf("\n");
}

int main() {
  input();
  solve();

  return 0;
}

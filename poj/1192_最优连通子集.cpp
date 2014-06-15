#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dp1(x, pre) (mo1[x] != -10000000 ? mo1[x] : _dp1(x, pre))
#define dp2(x, pre) (mo2[x] != -10000000 ? mo2[x] : _dp2(x, pre))

const int maxn = 1001;

int n;
int w[maxn];
int xi[maxn];
int yi[maxn];
int child[maxn][5];
int mo1[maxn];
int mo2[maxn];
int bucket[maxn+7][maxn+1];

int abs(int);

inline
int hash(int x, int y) {
  return abs((x * 107 + y * 3 ) % (maxn+6));
}

void input() {
  scanf("%d", &n);
  for (int i = 0; i < maxn+7; ++ i) 
    bucket[i][0] = 0;
  int tmp;
  for (int i = 0;i < n; ++ i) {
    scanf("%d %d %d", xi+i, yi+i, w+i);
    tmp = hash(xi[i], yi[i]);
    bucket[tmp][++bucket[tmp][0]] = i;
  }
}

inline
int abs(int x) {
  return x > 0 ? x : -x;
}

inline
int max(int a, int b) {
  return a > b ? a : b;
}

int _dp1(int x, int pre) {
  int ans = w[x];
  int tmp = 0;
  /*
  for (int s = 1; s < (1 << child[x][0]); ++ s) {
    tmp = 0;
    for (int i = 1; i <= child[x][0]; ++ i) {
      if (child[x][i] != pre && (1 << (i-1)) & s) {
        tmp += dp1(child[x][i], x);
      }
    }
    ans = max(ans, tmp + w[x]);
  }
  */
  for (int i = 1; i <= child[x][0]; ++ i) {
    if (child[x][i] != pre && dp1(child[x][i], x) > 0) {
      tmp += dp1(child[x][i], x);
    }
  }
  ans = max(ans, tmp+w[x]);

  return mo1[x] = ans;
}

int _dp2(int x, int pre) {
  int ans = w[x];
  for (int i = 1; i <= child[x][0]; ++ i) {
    if (child[x][i] == pre) continue;
    ans = max(ans, dp1(child[x][i], x));
    ans = max(ans, dp2(child[x][i], x));
  }

  return mo2[x] = ans;
}

int dir[][2] = {
  {0, 1}, {0, -1},
  {1, 0}, {-1, 0}
};
void solve() {
  //memset(child, 0, sizeof(child));
  int tmp;
  for (int i = 0; i < n; ++ i) {
    child[i][0] = 0;
    for (int j = 0; j < 4; ++ j) {
      tmp = hash(xi[i]+dir[j][0], yi[i]+dir[j][1]);
      for (int x = 1; x <= bucket[tmp][0]; ++ x) {
        if (xi[bucket[tmp][x]] == xi[i] + dir[j][0] and yi[bucket[tmp][x]] == yi[i]+dir[j][1]) {
          child[i][++child[i][0]] = bucket[tmp][x];
        }
      }
    }

    /*
    for (int j = 0; j < n; ++ j) {
      if (abs(xi[i]-xi[j]) + abs(yi[i]-yi[j]) == 1) {
        child[i][++child[i][0]] = j;
      }
    }
    */
  }
  for (int i = 0; i < n; ++ i) {
    mo1[i] = mo2[i] = -10000000;
  }
  printf("%d\n", max(dp1(0, -1), dp2(0, -1)));
}

int main() {
  input();
  solve();
  return 0;
}

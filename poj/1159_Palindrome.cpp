#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dp(i, j) (momo[i][j] != -1 ? momo[i][j] : _dp(i, j))

const int maxn = 5001;

int n;
char s[maxn];
short momo[maxn][maxn];

void input() {
  scanf("%d", &n);
  scanf("%s", s);
  memset(momo, -1 ,sizeof(momo));

  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j <= i; ++ j) {
      momo[i][j] = 0;
    }
  }

}

int _dp(int i, int j) {
  int min;
  int tmp;

  if (s[i] == s[j]) {
    return momo[i][j] = dp(i+1, j-1);
  }

  min = dp(i, j-1) + 1;
  tmp = dp(i+1, j) + 1;
  if (tmp < min) {
    min = tmp;
  }


  return momo[i][j] = min;
}

void solve() {
  int ans = dp(0, n-1);
  printf("%d\n", ans);
}

int main() {
  input();
  solve();

  return 0;
}


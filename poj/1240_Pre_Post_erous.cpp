#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 27;

char s1[maxn];
char s2[maxn];
int r1[maxn];
int r2[maxn];
int m;
int n;

int C[21][21];

void init() {
  for (int i = 0; i <= 20; ++ i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++ j) {
      C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
  }
}

int input() {
  scanf("%d", &m);
  if (not m) return 0;
  scanf("%s%s", s1, s2);
  n = strlen(s1);
  for (int i = 0; i < n; ++ i) {
    s1[i] = s1[i] - 'a';
    s2[i] = s2[i] - 'a';
    r1[(int)s1[i]] = i;
    r2[(int)s2[i]] = i;
  }
  return 1;
}

int dp(int begin, int end, int b2) {
  int ans = 1;
  int cnt = 0;
  int i = begin + 1;
  int j;
  if (begin == end) return 1;
  while (i <= end) {
    cnt += 1;
    j = r2[(int)s1[i]] - b2 + i;
    ans *= dp(i, j, b2);
    b2 = r2[(int)s1[i]] + 1;
    i = j + 1;
  }
  ans *= C[m][cnt];

  return ans;
}

void solve() {
  printf("%d\n", dp(0, n-1, 0));
}

int main() {
  init();
  while (input()) {
    solve();
  }

  return 0;
}

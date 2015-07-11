#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long int64;
const int64 MOD = (int64) 1e9+7;
const int maxn = 201;
int n;
int A[maxn][maxn];

void swap_col(int x, int y) {
  if (x == y) return;
  for (int i = 0; i < n; ++ i) {
    A[i][x] ^= A[i][y] ^= A[i][x] ^= A[i][y];
  }
}

int get_nonzero_col(int row) {
  for (int i = 0; i < n; ++ i) {
    if (A[row][i]) return i;
  }

  return n;
}

void minus_row(int x, int y, int c) {
  for (int i = 0; i < n; ++ i) {
    A[x][i] -= A[y][i] * c;
  }
}

int guass() {
  int col = 0;
  int cnt = 0;
  for (int row = 0; row < n; ++ row) {
    int nonzero = get_nonzero_col(row);
    if (nonzero == n) {
      cnt += 1;
      continue;
    }
    swap_col(nonzero, col);
    for (int i = row+1; i < n; ++ i) {
      minus_row(i, row, A[i][col]/A[row][col]);
    }
    col ++;
  }

  return cnt;
}

void solve() {
  int cnt = guass();
  int64 ans = 1;
  for (int i = 0; i < cnt; ++ i) {
    ans = ans * 99991 % MOD;
  }

  printf("%lld", ans);
}

int main() {
  scanf("%d", &n);
  memset(A, 0, sizeof(A));
  for (int i = 0; i < n; ++ i) {
    A[i][i] = -1;
    int c;
    scanf("%d", &c);
    for (int j = 0; j < c; ++ j) {
      int t;
      scanf("%d", &t);
      A[i][t-1] = 1;
    }
  }

  solve();


  return 0;
}


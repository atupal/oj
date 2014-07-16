
/*
   线性结构
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
//#include <unistd.h>

using namespace std;

const int maxn = 5001;
int n;
struct seg {
  int left;
  int right;
  int hight;
  int cover;
} *x, *y;

int cmp(const seg a, const seg b) {
  return a.hight < b.hight or (a.hight == b.hight and a.cover == -1);
}

void input() {
  x = (struct seg *) malloc (sizeof(struct seg) * maxn);
  y = (struct seg *) malloc (sizeof(struct seg) * maxn);
  scanf("%d", &n);
  int x1, y1, x2, y2;
  for (int i = 0; i < n; ++ i) {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    x[i<<1] = (struct seg) {x1, x2, y1, 1};
    x[(i<<1)+1] = (struct seg) {x1, x2, y2, -1};
    y[i<<1] = (struct seg) {y1, y2, x1, 1};
    y[(i<<1)+1] = (struct seg) {y1, y2, x2, -1};
  }
}

void qsort(struct seg *A, int l, int r) {
  if (l >= r) return;
  int p = l;
  for (int i = l+1; i <= r; ++ i) {
    if (cmp(A[i], A[l])) {
      ++ p;
      struct seg tmp = A[p];
      A[p] = A[i];
      A[i] = tmp;
    }
  }
  struct seg tmp = A[p];
  A[p] = A[l];
  A[l] = tmp;
  qsort(A, l, p-1);
  qsort(A, p+1, r);
}

int sum = 0;
void solve() {
  int _2n = n << 1;
  //sort(x, x+(n<<1), cmp);
  //sort(y, y+(n<<1), cmp);
  qsort(x, 0, _2n-1);
  qsort(y, 0, _2n-1);
  int t = 2;
  while (t--) {
    for (int i = 1; i < _2n; ++ i) {
      int l = y[i].hight - y[i-1].hight;
      if (not l) continue;
      int add = 0;
      int pre = -100000000;
      for (int j = 0; j < _2n; ++ j) if (x[j].left <= y[i-1].hight and x[j].right >= y[i].hight) {
        if (add == 0 and x[j].hight != pre) {
          sum += l;
        }
        add += x[j].cover;
        pre = x[j].hight;
      }
    }
    struct seg *tmp;
    tmp = x;
    x = y;
    y = tmp;
  }
  printf("%d\n", sum * 2);
}

int main() {
  input();
  solve();
  return 0;
}

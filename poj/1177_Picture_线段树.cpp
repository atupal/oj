/*
   线段树, 但元素不是区间, 而是点 ,
   所以在建树的时候要 (left, mid), (mid, right) 建立 而不是(left, mid), (mid+1, right)
   判断区间包含的时候, 注意用闭区间

   直接插入线段，然后判断,,没有用扫描线，其实跟暴力差不多，，，
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 50001;
int n;
struct seg {
  int left;
  int right;
  int hight;
  int cover;
} *x, *y;

static struct {
  int left;
  int right;
  int cover;
  int same;
} tree[maxn*20];

int cmp(const seg a, const seg b) {
  return a.hight < b.hight or (a.hight == b.hight and a.cover == -1);
}

void input() {
  scanf("%d", &n);
  x = (struct seg*) malloc (sizeof(struct seg) * maxn);
  y = (struct seg*) malloc (sizeof(struct seg) * maxn);
  int x1, y1, x2, y2;
  for (int i = 0; i < n; ++ i) {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    x[i<<1] = (struct seg) {x1, x2, y1, 1};
    x[(i<<1)+1] = (struct seg) {x1, x2, y2, -1};
    y[i<<1] = (struct seg) {y1, y2, x1, 1};
    y[(i<<1)+1] = (struct seg) {y1, y2, x2, -1};
  }
}

void build(int left, int right, int root) {
  //tree[root].left = left;
  //tree[root].right = right;
  tree[root].left = y[left-1].hight;
  tree[root].right = y[right-1].hight;
  tree[root].cover = 0;
  tree[root].same = 0;
  if (left == right-1) {
    tree[root].same = 1;
    return;
  }
  int mid = (left + right) >> 1;
  build(left, mid, root<<1);
  build(mid, right, (root<<1)+1);
}

int sum = 0;
int insert(int ind, int root) {
  if (x[ind].left >= tree[root].right or tree[root].left >= x[ind].right) {
    return 0;
  }
  if (tree[root].same) {
    if (tree[root].cover == 0) {
      int flag = 1;
      int tmp = ind;
      while (--tmp >= 0) {
        if (x[tmp].hight == x[ind].hight) {
          if (x[tmp].left <= tree[root].left and x[tmp].right >= tree[root].right) {
            flag = 0;
            break;
          }
        } else {
          break;
        }
      }
      //if (not(ind-1>=0 and x[ind-1].hight == x[ind].hight and x[ind-1].left <= tree[root].left and x[ind-1].right >= tree[root].right)) {
      if(flag) {
        sum += tree[root].right - tree[root].left;
        tree[root].cover += x[ind].cover;
        return tree[root].right - tree[root].left;
      }
    }
    tree[root].cover += x[ind].cover;
    return 0;
  }

  int t1 = insert(ind, root<<1);
  int t2 = insert(ind, (root<<1)+1);
  return t1 + t2;
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

void solve() {
  //sort(x, x+(n<<1), cmp);
  //sort(y, y+(n<<1), cmp);
  qsort(x, 0, (n<<1)-1);
  qsort(y, 0, (n<<1)-1);
  //build(-10000, 10000, 1);
  build(1, n<<1, 1);
  for (int i = 0; i < (n<<1)-1; ++ i) {
    int t = insert(i, 1);
    printf("%d %d %d\n", x[i].left, x[i].right, t);
  }
  //memcpy(x, y, sizeof(y));
  struct seg *tmp = x;
  x = y;
  y = tmp;
  //build(-10000, 10000, 1);
  build(1, n<<1, 1);
  for (int i = 0; i < (n<<1)-1; ++ i) {
    int t = insert(i, 1);
    printf("%d %d: %d\n", y[i].left, y[i].right, t);
  }
  printf("%d\n", sum*2);
}

int main() {
  input();
  solve();
  return 0;
}

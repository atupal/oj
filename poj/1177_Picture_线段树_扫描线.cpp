/*
   线段树, 但元素不是区间, 而是点 ,
   所以在建树的时候要 (left, mid), (mid, right) 建立 而不是(left, mid), (mid+1, right)
   判断区间包含的时候, 注意用闭区间

   扫描线

   数据结构的选择与算法效率——从IOI98试题PICTURE谈起
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  int M;
  int flag;
  int line;
  int lbd;
  int rbd;
} tree[maxn*20];

int cmp(const seg a, const seg b) {
  return a.hight < b.hight or (a.hight == b.hight and a.cover == 1);
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

void build(int left, int right, int root) {
  tree[root].left = x[left-1].hight;
  tree[root].right = x[right-1].hight;
  tree[root].cover = 0;
  tree[root].flag = 0;
  tree[root].lbd = 0;
  tree[root].rbd = 0;
  if (left == right-1) {
    tree[root].flag = 1;
    return;
  }
  int mid = (left + right) >> 1;
  build(left, mid, root<<1);
  build(mid, right, (root<<1)+1);
}

void update(int root) {
  if (tree[root].cover > 0) {
    tree[root].M = tree[root].right - tree[root].left;
    tree[root].line = 1;
    tree[root].lbd = 1;
    tree[root].rbd = 1;
  } else if (tree[root].flag) {
    tree[root].M = 0;
    tree[root].line = 0;
    tree[root].lbd = 0;
    tree[root].rbd = 0;
  } else {
    tree[root].M = tree[root<<1].M + tree[(root<<1)+1].M;
    /*忘记更新lbd，rbd了，，搞了好久*/
    tree[root].lbd = tree[root<<1].lbd;
    tree[root].rbd = tree[(root<<1)+1].rbd;
    tree[root].line = tree[root<<1].line + tree[(root<<1)+1].line
                    - tree[root<<1].rbd * tree[(root<<1)+1].lbd ;
  }
}

void insert(int left, int right, int value, int root) {
  if (left <= tree[root].left and right >= tree[root].right) {
    tree[root].cover += value;
    update(root);
    return;
  } else if (left >= tree[root].right or right <= tree[root].left) {
    return;
  }
  insert(left, right, value, root<<1);
  insert(left, right, value, (root<<1)+1);
  update(root);
}

void solve() {
  qsort(x, 0, (n<<1)-1);
  qsort(y, 0, (n<<1)-1);
  int sum = 0;
  build(1, (n<<1), 1);
  insert(y[0].left, y[0].right, y[0].cover, 1);
  int preM = tree[1].M;
  int preLine = tree[1].line;
  sum += preM;
  for (int i = 1; i < (n<<1); ++ i) {
    insert(y[i].left, y[i].right, y[i].cover, 1);
    sum += preLine * 2 * (y[i].hight - y[i-1].hight);
    sum += tree[1].M - preM > 0 ? tree[1].M - preM : preM - tree[1].M;
    preM = tree[1].M;
    preLine = tree[1].line;
  }
  printf("%d\n", sum);
}

int main() {
  input();
  solve();
  return 0;
}

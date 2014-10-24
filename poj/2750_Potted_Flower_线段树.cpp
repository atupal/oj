/*
 */
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#define lson (root<<1)
#define rson (root<<1|1)

const int maxn = 100010;
int n;

inline
int min(int a, int b) {
  return a < b ? a : b;
}
inline
int max(int a, int b) {
  return a > b ? a : b;
}

static struct {
  int left;
  int right;
  int min;
  int max;
  int lmin;
  int lmax;
  int rmin;
  int rmax;
  int sum;
} tree[maxn*3+10];

void update(int);

#define init(root) \
    tree[root].max = tree[root].min;\
    tree[root].lmin = tree[root].min;\
    tree[root].lmax = tree[root].min;\
    tree[root].rmin = tree[root].min;\
    tree[root].rmax = tree[root].min;\
    tree[root].sum = tree[root].min;\

void build(int root, int left, int right) {
  tree[root].left = left;
  tree[root].right = right;
  if (left == right) {
    scanf("%d", &tree[root].min);
    init(root);
    return;
  }
  int mid = (left + right) >> 1;
  build(lson, left, mid);
  build(rson, mid+1, right);
  update(root);
}

void update(int root) {
  tree[root].sum = tree[lson].sum + tree[rson].sum;
  tree[root].min = min(tree[lson].min, tree[rson].min);
  tree[root].max = max(tree[lson].max, tree[rson].max);
  tree[root].min = min(tree[root].min, tree[lson].rmin + tree[rson].lmin);
  tree[root].max = max(tree[root].max, tree[lson].rmax + tree[rson].lmax);
  tree[root].lmin = tree[lson].lmin;
  if (tree[lson].lmin == tree[lson].sum) {
    tree[root].lmin = min(tree[root].lmin, tree[lson].lmin + tree[rson].lmin);
  }
  tree[root].lmax = tree[lson].lmax;
  if (tree[lson].lmax == tree[lson].sum) {
    tree[root].lmax = max(tree[root].lmax, tree[lson].lmax + tree[rson].lmax);
  }
  tree[root].rmin = tree[rson].rmin;
  if (tree[rson].rmin == tree[rson].sum) {
    tree[root].rmin = min(tree[root].rmin, tree[rson].rmin + tree[lson].rmin);
  }
  tree[root].rmax = tree[rson].rmax;
  if (tree[rson].rmax == tree[rson].sum) {
    tree[root].rmax = max(tree[root].rmax, tree[rson].rmax + tree[lson].rmax);
  }
}

void insert(int root, int left, int right, int c) {
  if (left <= tree[root].left && tree[root].right <= right) {
    tree[root].min = c;
    init(root);
    return;
  } else if (tree[root].left > right || tree[root].right < left) {
    return;
  }
  insert(lson, left, right, c);
  insert(rson, left, right, c);
  update(root);
}

void solve() {
  int m;
  build(1, 1, n);
  scanf("%d", &m);
  for (int i = 0; i < m; ++ i) {
    int a, b;
    scanf("%d %d", &a, &b);
    insert(1, a, a, b);
    // 忘了不能全取。。。。
    if (tree[1].max != tree[1].sum)
      printf("%d\n", max(tree[1].max, tree[1].sum - tree[1].min));
    else
      printf("%d\n", tree[1].sum - tree[1].min);
  }
}

int main() {
  scanf("%d", &n);
  solve();
  return 0;
}

/**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lson (root<<1)
#define rson (root<<1|1)

const int maxn = 100010;
int n, q;
int cache[maxn];

static struct {
  int left;
  int right;
  int lbd;
  int lval;
  int rbd;
  int rval;
  int maxbd;
  int maxval;
  int len;
  int mask;
} tree[maxn*3+1];

void build(int root, int left, int right) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].lbd = 0;
  tree[root].rbd = 0;
  tree[root].lval = maxn;
  tree[root].rval = maxn;
  tree[root].maxbd = 0;
  tree[root].maxval = maxn;
  tree[root].len = right - left + 1;
  tree[root].mask = 0;
  if (left == right) {
    return;
  }
  int mid = (left + right) >> 1;
  build(lson, left, mid);
  build(rson, mid+1, right);
}

#define init(root) \
    tree[root].lbd = tree[root].len; \
    tree[root].lval = c; \
    tree[root].rbd = tree[root].len; \
    tree[root].rval = c; \
    tree[root].maxbd = tree[root].len; \
    tree[root].maxval = c; \
    tree[root].mask = 1;
void push_down(int root) {
  if (tree[root].mask) {
    tree[root].mask = 0;
    int c = tree[root].maxval;
    init(lson);
    init(rson);
  }
}

void update(int root) {
  tree[root].lval = tree[lson].lval;
  tree[root].lbd = tree[lson].lbd;
  tree[root].rval = tree[rson].rval;
  tree[root].rbd = tree[rson].rbd;
  if (tree[lson].maxbd >= tree[rson].maxbd) {
    tree[root].maxbd = tree[lson].maxbd;
    tree[root].maxval = tree[lson].maxval;
  } else {
    tree[root].maxbd = tree[rson].maxbd;
    tree[root].maxval = tree[rson].maxval;
  }
  if (tree[lson].lbd == tree[lson].len and tree[lson].lval == tree[rson].lval) {
    tree[root].lbd = tree[lson].len + tree[rson].lbd;
  }
  if (tree[rson].rbd == tree[rson].len and tree[rson].rval == tree[lson].rval) {
    tree[root].rbd = tree[rson].len = tree[lson].rbd;
  }
  if (tree[lson].rval == tree[rson].lval and tree[lson].rbd + tree[rson].lbd > tree[root].maxbd) {
    tree[root].maxbd = tree[lson].rbd + tree[rson].lbd;
    tree[root].maxval = tree[lson].rval;
  }
}

void insert(int root, int left, int right, int c) {
  if (left <= tree[root].left and tree[root].right <= right) {
    init(root);
    return;
  } else if (tree[root].left > right or tree[root].right < left) {
    return;
  }
  push_down(root);
  insert(lson, left, right, c);
  insert(rson, left, right, c);
  update(root);
}

#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))
int query(int root, int left, int right) {
  if (left <= tree[root].left and tree[root].right <= right) {
    return tree[root].maxbd;
  } else if (tree[root].left > right or tree[root].right < left) {
    return 0;
  }
  push_down(root);
  int lbd = query(lson, left, right);
  int rbd = query(rson, left, right);
  int mbd = 0;
  if (tree[lson].rval == tree[rson].lval) {
    int l, r;
    l = max(left, tree[lson].right - tree[lson].rbd + 1);
    r = min(right, tree[rson].left + tree[rson].lbd - 1);
    mbd = r - l + 1;
  }
  return max(lbd, max(rbd, mbd));
}

int solve() {
  if (not(scanf("%d", &n), n)) return 0;
  build(1, 1, n);
  scanf("%d", &q);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", cache + i);
  }
  int cnt = 0, pre;
  while (cnt < n) {
    int tmp = cnt;
    pre = cache[tmp];
    while (cnt+1 < n and cache[cnt+1] == pre) ++ cnt;
    insert(1, tmp+1, cnt+1, pre);
    ++ cnt;
  }
  int a, b;
  for (int i = 0; i < q; ++ i) {
    scanf("%d %d", &a, &b);
    printf("%d\n", query(1, a, b));
  }
  return 1;
}

int main() {
  while(solve());
  return 0;
}

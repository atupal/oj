/*
   lbd 左边的连续的空位
   rbd 右边的连续的空位
   maxbx 最长的连续空位
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))

const int maxn = 50010;
int n, m;

static struct {
  int left;
  int right;
  int mask;
  int lbd;
  int rbd;
  int maxbd;
  int len;
} tree[maxn*3+1];

void build(int root, int left, int right) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].mask = 0;
  tree[root].len = right - left + 1;
  tree[root].lbd = tree[root].len;
  tree[root].rbd = tree[root].len;
  tree[root].maxbd = tree[root].len;
  if (left >= right) {
    return;
  }
  int mid = (left + right) >> 1;
  build(root<<1, left, mid);
  build(root<<1|1, mid+1, right);
}

inline
void push_down(int root) {
  if (tree[root].mask == 1) {
    tree[root].mask = 0;
    tree[root<<1].lbd = 0;
    tree[root<<1].rbd = 0;
    tree[root<<1].maxbd = 0;
    tree[root<<1|1].lbd = 0;
    tree[root<<1|1].rbd = 0;
    tree[root<<1|1].maxbd = 0;
    // 标记不要也要忘了往下传
    tree[root<<1].mask = 1;
    tree[root<<1|1].mask = 1;
  } else if (tree[root].mask == 2) {
    tree[root].mask = 0;
    tree[root<<1].lbd = tree[root<<1].len;
    tree[root<<1].rbd = tree[root<<1].len;
    tree[root<<1].maxbd = tree[root<<1].len;
    tree[root<<1|1].lbd = tree[root<<1|1].len;
    tree[root<<1|1].rbd = tree[root<<1|1].len;
    tree[root<<1|1].maxbd = tree[root<<1|1].len;
    tree[root<<1].mask = 2;
    tree[root<<1|1].mask = 2;
  }
}

inline
void update(int root) {
  // 妈蛋，终于 ac 了，这里不能再依赖 tree[root].lbd rbd ，因为已经无效了，不能再使用，
  // 只应该使用 子节点的 信息来更新
  if (tree[root<<1].lbd == tree[root<<1].len) {
    tree[root].lbd = tree[root<<1|1].lbd + tree[root<<1].len;
  } else {
    tree[root].lbd = tree[root<<1].lbd;
  }
  if (tree[root<<1|1].rbd == tree[root<<1|1].len) {
    tree[root].rbd = tree[root<<1].rbd + tree[root<<1|1].len;
  } else {
    tree[root].rbd = tree[root<<1|1].rbd;
  }
  // 同上，这里不需要tree[root].maxbd 的信息，应该丢弃这个信息，因为已经过时了。
  tree[root].maxbd = max(tree[root].lbd, tree[root].rbd);
  tree[root].maxbd = max(tree[root<<1].maxbd, tree[root].maxbd);
  tree[root].maxbd = max(tree[root<<1|1].maxbd, tree[root].maxbd);
  tree[root].maxbd = max(tree[root<<1].rbd + tree[root<<1|1].lbd, tree[root].maxbd);
}

void insert(int root, int left, int right) {
  if (left <= tree[root].left and tree[root].right <= right) {
    tree[root].lbd = 0;
    tree[root].rbd = 0;
    tree[root].maxbd = 0;
    tree[root].mask = 1;
    return;
  } else if (tree[root].left > right or tree[root].right < left) {
    return;
  }
  tree[root].lbd = min(max(0, left - tree[root].left), tree[root].lbd);
  tree[root].rbd = min(max(0, tree[root].right - right), tree[root].rbd);
  push_down(root);
  insert(root<<1, left, right);
  insert(root<<1|1, left, right);
  update(root);
}

void del(int root, int left, int right) {
  if (left <= tree[root].left and tree[root].right <= right) {
    tree[root].lbd = tree[root].len;
    tree[root].rbd = tree[root].len;
    tree[root].maxbd = tree[root].len;
    tree[root].mask = 2;
    return;
  } else if (tree[root].left > right or tree[root].right < left) {
    return;
  }
  if (left <= tree[root].left + tree[root].lbd) {
    tree[root].lbd = max(min(tree[root].len, right - tree[root].left + 1), tree[root].lbd);
  }
  if (right >= tree[root].right - tree[root].rbd) {
    tree[root].rbd = max(min(tree[root].len, tree[root].right - left + 1), tree[root].rbd);
  }
  push_down(root);
  del(root<<1, left, right);
  del(root<<1|1, left, right);
  update(root);
}

int query(int root, int d) {
  // 不需要 push_down ,因为这里只要 max 信息就可以了，而这个信息每次都会 往上 update，所以信息是足够的
  if (tree[root].maxbd < d) {
    return 0;
  }
  if (tree[root].lbd >= d) {
    return tree[root].left;
  }
  if (tree[root<<1].maxbd >= d) {
    return query(root<<1, d);
  }
  if (tree[root<<1].rbd + tree[root<<1|1].lbd >= d) {
    return tree[root<<1].right - tree[root<<1].rbd + 1;
  }
  if (tree[root<<1|1].maxbd >= d) {
    return query(root<<1|1, d);
  }
  return 0;
}

void solve() {
  build(1, 1, n);
  int x, a, b, t;
  for (int i = 0; i < m; ++ i) {
    scanf("%d %d", &x, &a);
    if (x == 1) {
      t = query(1, a);
      printf("%d\n", t);
      if (t) {
        insert(1, t, t+a-1);
      }
    } else {
      scanf("%d", &b);
      del(1, a, a+b-1);
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  solve();
  return 0;
}

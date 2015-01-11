#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lson root<<1
#define rson root<<1|1

const int maxn = 2e5+10;
static struct {
  int left;
  int right;
  int sum;
  int ll;
  int rr;
  int mask;
} tree[maxn<<2];
int n;
int q;

void build(int root, int left, int right) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].mask = 0;
  if (left == right) {
    scanf("%d", &tree[root].sum);
    tree[root].ll = tree[root].rr = tree[root].sum;
    return;
  }
  int mid = (left+right)>>1;
  build(lson, left, mid);
  build(rson, mid+1, right);
  tree[root].ll = tree[lson].ll;
  tree[root].rr = tree[rson].rr;
}
 
void push_down(int root) {
}

void update(int root) {
}

void insert(int root, int left, int right) {
  if ( left <= tree[root].left && tree[root].right <= right 
      && (tree[root].right - tree[root].left)&1) {
    tree[root].mask = !tree[root].mask;
    return;
  } else if ( left > tree[root].right || right < tree[root].left ) {
    return;
  }
  push_down(root);
  update(root);
}

void solve() {
  build(1, 1, n);
  for (int i = 0; i < q; ++ i) {
    int op[3];
    scanf("%d %d %d", op, op+1, op+2);
    if (op[0] == 1) {
    } else if (op[0] == 2) {
    }
  }
}


int main() {
  scanf("%d %d", &n, &q);
  solve();

  return 0;
}

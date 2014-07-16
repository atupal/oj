#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

const int maxn = 100001;

int n,q;
typedef long long int64;

static struct {
  int left;
  int right;
  int64 sum;
  int64 mark;
} tree[maxn*3];

void build(int left, int right, int root) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].mark = 0L;
  if (left == right) {
    scanf("%lld", &tree[root].sum);
    return;
  }
  int mid = (left + right) >> 1;
  build(left, mid, root*2);
  build(mid+1, right, root*2+1);
  tree[root].sum = tree[root*2].sum + tree[root*2+1].sum;
}

void push_down(int root) {
  if (tree[root].mark != 0L) {
    tree[root*2].mark += tree[root].mark;
    tree[root*2+1].mark += tree[root].mark;
    tree[root*2].sum += tree[root].mark * (tree[root*2].right - tree[root*2].left + 1);
    tree[root*2+1].sum += tree[root].mark * (tree[root*2+1].right - tree[root*2+1].left + 1);
    tree[root].mark = 0L;
  }
}

void add(int left, int right, int64 c, int root) {
  if (left <= tree[root].left and tree[root].right <= right) {
    tree[root].sum += c * (tree[root].right - tree[root].left + 1);
    tree[root].mark += c;
    return;
  } else if (left > tree[root].right or right < tree[root].left) {
    return;
  }
  push_down(root);
  add(left, right, c, root*2);
  add(left, right, c, root*2+1);
  tree[root].sum = tree[root*2].sum + tree[root*2+1].sum;
}

int64 query(int left, int right, int root) {
  if (left <= tree[root].left and tree[root].right <= right) {
    return tree[root].sum;
  } else if (left > tree[root].right or right < tree[root].left) {
    return 0L;
  }
  push_down(root);
  return query(left, right, root*2) + query(left, right, root*2+1);
}

void solve() {
  scanf("%d %d", &n, &q);
  build(1, n, 1);
  char s[2];
  int a, b;
  int64 c;
  for (int i = 0; i < q; ++ i) {
    scanf("%s %d %d", s, &a, &b);
    if (s[0] == 'C') {
      scanf("%lld", &c);
      add(a, b, c, 1);
    } else {
      printf("%lld\n", query(a, b, 1));
    }
  }
}

int main() {
  solve();

  return 0;
}

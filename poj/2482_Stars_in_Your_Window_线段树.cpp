/**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define lson (root<<1)
#define rson (root<<1|1)
#define max(a, b) ((a)>(b)?(a):(b))

const int maxn = 100100;
int n, w, h;
int X[maxn];

typedef unsigned int lint;

static struct {
  lint left;
  lint right;
  int cover;
  int mask;
  int max;
} tree[maxn*3+1];

struct line {
  lint left;
  lint right;
  int hight;
  int val;
} lines[maxn<<1];

void build(int root, lint left, lint right) {
  tree[root].left = X[left];
  tree[root].right = X[right];
  tree[root].cover = 0;
  tree[root].mask = 0;
  tree[root].max = 0;
  if (left == right) {
    return;
  }
  lint mid = (left + right) >> 1;
  build(lson, left, mid);
  build(rson, mid+1, right);
}

void push_down(int root) {
  if (tree[root].mask) {
    tree[lson].cover += tree[root].mask;
    tree[rson].cover += tree[root].mask;
    tree[lson].max += tree[root].mask;
    tree[rson].max += tree[root].mask;
    tree[lson].mask = tree[root].mask;
    tree[rson].mask = tree[root].mask;
    tree[root].mask = 0;
  }
}

void update(int root) {
  tree[root].max = max(tree[lson].max, tree[rson].max);
}

void insert(int root, lint left, lint right, int c) {
  if (left <= tree[root].left and tree[root].right <= right) {
    tree[root].cover += c;
    tree[root].max += c;
    tree[root].mask = c;
    return;
  } else if (left > tree[root].right or right < tree[root].left) {
    return;
  }
  push_down(root);
  insert(lson, left, right, c);
  insert(rson, left, right, c);
  update(root);
}

int cmp(const line a, const line b) {
  return a.hight < b.hight or (a.hight == b.hight and a.val > 0);
}

void solve() {
  int ans = 0;
  int i = 0, j = 0, t;
  sort(X, X+n);
  while (j < n) {
    t = X[j];
    while (j+1 < n and X[j+1] == t) ++ j;
    X[i] = t;
    ++ i;
    ++ j;
  }
  build(1, 0, i-1);
  sort(lines, lines+(n<<1), cmp);
  int _2n = n << 1;
  for (int i = 0; i < _2n; ++ i) {
    insert(1, lines[i].left, lines[i].right, lines[i].val);
    ans = max(ans, tree[1].max);
  }
  printf("%d\n", ans);
}

int input() {
  if (scanf("%d %d %d", &n, &w, &h) == EOF) return 0;
  int x, y, c;
  for (int i = 0; i < n; ++ i) {
    scanf("%d %d %d", &x, &y, &c);
    X[i] = x;
    lines[i<<1].left = max(0, x - w + 1);
    lines[i<<1].right = max(0, x + w - 1);
    lines[i<<1].hight = max(0, y - h + 1);
    lines[i<<1].val = c;

    lines[i<<1|1].left = max(0, x - w + 1);
    lines[i<<1|1].right = max(0, x + w - 1);
    lines[i<<1|1].hight = max(0, y + h - 1);
    lines[i<<1|1].val = -c;
  }
  return 1;
}

int main() {
  while (input())
    solve();
  return 0;
}

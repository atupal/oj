/*
   对每个星星来说，左上角在以这个星星为右下顶点的矩形内部的矩形都可以围住这个星星。
   note：
        1. 离散化时为闭区间（a，b），因为边界不算。
        2. mask 是累加的
        3. 高度相等时，出边应该排在前面，同1
   计算最大的重叠的矩形的值的和即可。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define lson (root<<1)
#define rson (root<<1|1)
#define max(a, b) ((a)>(b)?(a):(b))

typedef long long lint;

const int maxn = 100100;
int n;
lint w, h;
lint X[maxn<<1];


static struct {
  lint left;
  lint right;
  int cover;
  int mask;
  int max;
} tree[maxn*3];

struct line {
  lint left;
  lint right;
  lint hight;
  lint val;
} lines[maxn<<1];

void build(int root, int left, int right) {
  tree[root].left = X[left];
  tree[root].right = X[right];
  tree[root].cover = 0;
  tree[root].mask = 0;
  tree[root].max = 0;
  if (left >= right-1) {
    return;
  }
  lint mid = (left + right) >> 1;
  build(lson, left, mid);
  build(rson, mid, right);
}

void push_down(int root) {
  if (tree[root].mask) {
    tree[lson].cover += tree[root].mask;
    tree[rson].cover += tree[root].mask;
    tree[lson].max += tree[root].mask;
    tree[rson].max += tree[root].mask;
    tree[lson].mask += tree[root].mask;
    tree[rson].mask += tree[root].mask;
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
    tree[root].mask += c;
    return;
  } else if (left >= tree[root].right or right <= tree[root].left) {
    return;
  }
  push_down(root);
  insert(lson, left, right, c);
  insert(rson, left, right, c);
  update(root);
}

int cmp(const line a, const line b) {
  return a.hight < b.hight or (a.hight == b.hight and a.val < 0);
}

void solve() {
  int ans = 0;
  int i = 0, j = 0, t;
  int _2n = n << 1;
  sort(X, X+_2n);
  while (j < _2n) {
    t = X[j];
    while (j+1 < _2n and X[j+1] == t) ++ j;
    X[i] = t;
    ++ i;
    ++ j;
  }
  build(1, 0, i-1);
  sort(lines, lines+_2n, cmp);
  for (int i = 0; i < _2n; ++ i) {
    insert(1, lines[i].left, lines[i].right, lines[i].val);
    ans = max(ans, tree[1].max);
  }
  printf("%d\n", ans);
}

int input() {
  if (scanf("%d %lld %lld", &n, &w, &h) == EOF) return 0;
  lint x, y;
  int c;
  for (int i = 0; i < n; ++ i) {
    scanf("%lld %lld %d", &x, &y, &c);
    X[i<<1] = x;
    X[i<<1|1] = x - w;
    lines[i<<1].left = x - w;
    lines[i<<1].right = x;
    lines[i<<1].hight = y;
    lines[i<<1].val = c;

    lines[i<<1|1].left = x - w;
    lines[i<<1|1].right = x;
    lines[i<<1|1].hight = y + h;
    lines[i<<1|1].val = -c;

    //printf("(%d, %d): %d - %d\n", x, y, lines[i<<1].left, lines[i<<1].right);
  }
  return 1;
}

int main() {
  while (input())
    solve();
  return 0;
}

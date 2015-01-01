/*
   可持久化线段树
   不修改的区间 k 大问题
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 1e5+1;
int a[maxn];
int s[maxn];
int cnt;
int n, m;
int idx;

static struct {
  int lson;
  int rson;
  int cnt;
} tree[maxn<<5];
int root[maxn];

int insert(int root, int left, int right, int pos, int c) {
  int copy_root = ++idx;
  tree[copy_root].lson = tree[root].lson;
  tree[copy_root].rson = tree[root].rson;
  tree[copy_root].cnt = tree[root].cnt + c;
  if (left == right) return copy_root;
  int mid = (left+right) >> 1;
  if (mid < pos) {
    tree[copy_root].rson = insert(tree[root].rson, mid+1, right, pos, c);
  } else {
    tree[copy_root].lson = insert(tree[root].lson, left, mid, pos, c);
  }
  return copy_root;
}

int query(int root_r, int root_l, int left, int right, int k) {
  if (left == right) return left;
  int mid = (left+right)>>1;
  int l = tree[ tree[root_r].lson ].cnt - tree[ tree[root_l].lson ].cnt;
  if (l < k) {
    return query(tree[root_r].rson, tree[root_l].rson, mid+1, right, k-l);
  } else {
    return query(tree[root_r].lson, tree[root_l].lson, left, mid, k);
  }
}

void solve() {
  memset(tree, 0, sizeof(tree));
  sort(a+1, a+n+1);
  cnt = unique(a+1, a+n+1) - (a+1);
  idx = 0;
  root[0] = 0;
  for (int i = 1; i <= n; ++ i) {
    int pos = lower_bound(a+1, a+cnt+1, s[i]) - a;
    root[i] = insert(root[i-1], 1, cnt, pos, 1);
  }
  int l, r, k;
  for (int i = 0; i < m; ++ i) {
    scanf("%d %d %d", &l, &r, &k);
    printf("%d\n", a[  query(root[r], root[l-1], 1, cnt, k)  ]);
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++ i) {
    scanf("%d", a+i);
    s[i] = a[i];
  }
  solve();

  return 0;
}

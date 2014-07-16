#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

const int maxn = 50001;


int n,q;

static struct {
  int left;
  int right;
  int max;
  int min;
} tree[maxn*3];

inline
void build(int left, int right, int root) {
  tree[root].left = left;
  tree[root].right = right;
  if (left == right) {
    scanf("%d", &tree[root].max);
    tree[root].min = tree[root].max;
    return;
  }
  int mid = (left+right) >> 1;
  build(left, mid, root<<1);
  build(mid+1, right, (root<<1)+1);
  tree[root].min = min(tree[root<<1].min, tree[(root<<1)+1].min);
  tree[root].max = max(tree[root<<1].max, tree[(root<<1)+1].max);
}

inline
int query_max(int left, int right, int root) {
  if (left <= tree[root].left and tree[root].right <= right) {
    return tree[root].max;
  } else if (left > tree[root].right or right < tree[root].left) {
    return 0;
  }
  int t1 = query_max(left, right, root<<1);
  int t2 = query_max(left, right, (root<<1)+1);
  return max(t1, t2);
}

inline
int query_min(int left, int right, int root) {
  if (left <= tree[root].left and tree[root].right <= right) {
    return tree[root].min;
  } else if (left > tree[root].right or right < tree[root].left) {
    return 100000000;
  }
  /*
     不然会超时!不要重复计算
   */
  int t1 = query_min(left, right, root<<1);
  int t2 = query_min(left, right, (root<<1)+1);
  return min(t1, t2);
}

void solve() {
  scanf("%d %d", &n, &q);
  build(1, n, 1);
  int a, b;
  int t1, t2;
  while (q --) {
    scanf("%d %d", &a, &b);
    t1 = query_max(a, b, 1);
    t2 = query_min(a, b, 1);
    printf("%d\n", t1 - t2);
  }
}

int main() {
  solve();
  return 0;
}

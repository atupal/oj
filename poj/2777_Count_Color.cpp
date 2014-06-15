/*
   线段树
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 100002;
int l, t, o;

static struct T{
  int left;
  int right;
  int mark;
} tree[maxn*3];

inline
int bitcount(int x) {
  x = (x & 0x55555555) + ((x >> 1) & 0x55555555); 
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333); 
  x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F); 
  x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF); 
  x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
  return x;
}

inline
void build(int left, int right, int root) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].mark = 1;
  if (left == right) {
    return;
  }
  int mid = (left + right) >> 1;
  build(left, mid, root*2);
  build(mid+1, right, root*2 + 1);
}

inline
void change(int left, int right, int color, int root) {
  if (tree[root].left >= left and tree[root].right <= right) {
    tree[root].mark = 1 << (color-1);
    return;
  } else if (tree[root].left > right or tree[root].right < left) {
    return;
  }
  // push_down 标记往下传
  if (tree[root].mark != 0) {
    tree[root*2].mark = tree[root].mark;
    tree[root*2+1].mark = tree[root].mark;
    tree[root].mark = 0;
  }
  change(left, right, color, root*2);
  change(left, right, color, root*2+1);
  
  // update 子节点可能改变了, 更新标记
  if (tree[root*2].mark == tree[root*2+1].mark and tree[root].mark == 0) {
    tree[root].mark = tree[root*2].mark;
  }
}

inline
int query(int left, int right, int root) {
	if(tree[root].left >= left and tree[root].right <= right and tree[root].mark) {
		return tree[root].mark;
  } else if (tree[root].left > right or tree[root].right < left) {
    return 0;
  }
  if (tree[root].mark != 0) {
    tree[root*2].mark = tree[root].mark;
    tree[root*2+1].mark = tree[root].mark;
    tree[root].mark = 0;
  }
  if (tree[root*2].mark == tree[root*2+1].mark and tree[root].mark == 0) {
    tree[root].mark = tree[root*2].mark;
  }
  return query(left, right, root*2) | query(left, right, root*2+1);
}

void solve() {
  scanf("%d %d %d", &l, &t, &o);
  char a[2];
  int left, right, color;
  build(1, l, 1);
  for (int i = 0; i < o; ++ i) {
    scanf("%s %d %d", a, &left, &right);
    if (left > right) left ^= right ^= left ^= right;
    if (a[0] == 'C') {
      scanf("%d", &color);
      change(left, right, color, 1);
    } else {
      int colorbit = query(left, right, 1);
      printf("%d\n", bitcount(colorbit));
    }
  }
}

int main() {
  solve();
  return 0;
}

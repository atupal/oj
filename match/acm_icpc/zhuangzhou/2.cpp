#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 1000100;
int l, t, o;

static struct T{
  int left;
  int right;
  //long long mark;
  int mark;
} tree[maxn*3];

void build(int left, int right, int root) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].mark = 2;
  if (left == right) {
    return;
  }
  int mid = (left + right) >> 1;
  build(left, mid, root*2);
  build(mid+1, right, root*2 + 1);
}

inline
void change(int left, int right, int color, int root) {
  if (tree[root].left >= left && tree[root].right <= right) {
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
  if (tree[root*2].mark == tree[root*2+1].mark && tree[root].mark == 0) {
    tree[root].mark = tree[root*2].mark;
  }
}

inline
int query(int left, int right, int root) {
	if(tree[root].left >= left && tree[root].right <= right && tree[root].mark) {
		return tree[root].mark;
  } else if (tree[root].left > right or tree[root].right < left) {
    return 0;
  }
  if (tree[root].mark != 0) {
    tree[root*2].mark = tree[root].mark;
    tree[root*2+1].mark = tree[root].mark;
    tree[root].mark = 0;
  }
  if (tree[root*2].mark == tree[root*2+1].mark && tree[root].mark == 0) {
    tree[root].mark = tree[root*2].mark;
  }
  return query(left, right, root*2) | query(left, right, root*2+1);
}

void out(int bit) {
    int t[32];
    memset(t, 0, sizeof(t));
    int cnt = 0;
    for (int i = 0; i < 30; ++ i) {
        int mask = 1<<i;
        if (bit & mask) {
            t[cnt++] = i+1;
        }
    }
    for (int i = 0; i < cnt-1; ++ i) {
        printf("%d ", t[i]);
    }
    printf("%d\n", t[cnt-1]);
}

void solve() {
  //scanf("%d %d %d", &l, &t, &o);
  char a[2];
  int left, right, color;
  build(1, l, 1);
  for (int i = 0; i < o; ++ i) {
    scanf("%s %d %d", a, &left, &right);
    //if (left > right) left ^= right ^= left ^= right;
    if (a[0] == 'P') {
      scanf("%d", &color);
      change(left, right, color, 1);
    } else {
      int colorbit = query(left, right, 1);
      out(colorbit);
    }
  }
}

int main() {
    while (1) {
        scanf("%d %d", &l, &o);
        if (!l && !o) break; 
        solve();
    }
  return 0;
}

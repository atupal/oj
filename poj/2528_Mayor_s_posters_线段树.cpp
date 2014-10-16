/*
   线段树, 离散化
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 100100;

int n;
int l[maxn];
int r[maxn];
int ans[maxn];
int *s[maxn*2];
int cnt;

static struct {
  int left;
  int right;
  int mark;
} tree[maxn*3];

void swap(int a, int b) {
  int *t = s[a];
  s[a] = s[b];
  s[b] = t;
}

void qsort(int l, int r) {
  if (l >= r) return;
  int p = l;
  for (int i = l+1; i <= r; ++ i) {
    if (*(s[i]) < *(s[l])) {
      swap(++p, i);
    }
  }
  swap(p, l);
  qsort(l, p-1);
  qsort(p+1, r);
}

void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d %d", l+i, r+i);
    s[i*2] = l+i;
    s[i*2+1] = r+i;
  }
}

void build(int left, int right, int root) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].mark = 0;
  if (left == right) {
    return;
  }
  int mid = (left + right) >> 1;
  build(left, mid, root*2);
  build(mid+1, right, root*2+1);
}

void insert(int left, int right, int poster, int root) {
  if (tree[root].left >= left and tree[root].right <= right) {
    tree[root].mark = poster;
    return;
  } else if (tree[root].left > right or tree[root].right < left) {
    return;
  }
  if (tree[root].mark) {
    tree[root*2].mark = tree[root].mark;
    tree[root*2+1].mark = tree[root].mark;
    tree[root].mark = 0;
  }
  insert(left, right, poster, root*2);
  insert(left, right, poster, root*2+1);
  if (tree[root*2].mark == tree[root*2+1].mark and tree[root].mark == 0) {
    tree[root].mark = tree[root*2].mark;
  }
}

int query(int x, int root) {
  if (tree[root].left == tree[root].right or tree[root].mark)
    return tree[root].mark;
  if (tree[root].mark) {
    tree[root*2].mark = tree[root].mark;
    tree[root*2+1].mark = tree[root].mark;
    tree[root].mark = 0;
  }
  if (tree[root*2].mark == tree[root*2+1].mark and tree[root].mark == 0) {
    tree[root].mark = tree[root*2].mark;
  }
  int mid = (tree[root].left + tree[root].right) >> 1;
  if (x <= mid) {
    return query(x, root*2);
  } else {
    return query(x, root*2+1);
  }
}

void solve() {
  qsort(0, n*2-1);
  int pre = *s[0];
  cnt = 1;
  *(s[0]) = cnt;
  for (int i = 1; i < 2*n; ++ i) {
    //离散化 
    if (*s[i] != pre) {
      if (*s[i] - pre > 1)
        cnt += 2;
      else
        cnt += 1;
    }
    pre = *s[i];
    *s[i] = cnt;
  }

  build(1, cnt, 1);
  for (int i = 0; i < n; ++ i) {
    insert(l[i], r[i], i+1, 1);
  }
  int count = 0;
  memset(ans, 0, sizeof(ans));
  for (int i = 1; i <= cnt; ++ i) {
    ans[query(i, 1)] = 1;
  }
  for (int i = 1; i <= cnt; ++ i) if (ans[i])
    count += 1;
  printf("%d\n", count);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    input();
    solve();
  }
  return 0;
}


/*
   3
   3
   5 6
   4 5
   6 8
   3
   1 10
   1 3
   6 10
   5
   1 4
   2 6
   8 10
   3 4
   7 10
   正确答案应该是：
   3
   3
   4
   很多人的答案是：
   2
   2
   4
   
   是2、3、4，得2、2、4是因为离散化忽略了顺序相邻但位置不相邻的情况
 */

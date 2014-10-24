#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 810;

int n;

typedef long long int64;

int64 p[maxn][maxn];

inline
int64 min(int64 a, int64 b) {
  return a < b ? a : b;
}
inline
int64 max(int64 a, int64 b) {
  return a > b ? a : b;
}

static struct {
  int x1, y1, x2, y2;
  int son1, son2, son3, son4;
  int is_null_node;
  int64 min, max;
} tree[maxn*10000+1];

void update(int root) {
  tree[root].min = min( min(tree[tree[root].son1].min, tree[tree[root].son2].min),
                        min(tree[tree[root].son3].min, tree[tree[root].son4].min) );
  tree[root].max = max( max(tree[tree[root].son1].max, tree[tree[root].son2].max),
                        max(tree[tree[root].son3].max, tree[tree[root].son4].max) );
}

int cnt;
void build(int root, int x1, int y1, int x2, int y2, int is_null_node) {
  //printf("%d %d %d %d\n", x1, y1, x2, y2);
  tree[root].x1 = x1;
  tree[root].y1 = y1;
  tree[root].x2 = x2;
  tree[root].y2 = y2;
  tree[root].min = (int64)10e15;
  tree[root].max = -1;
  tree[root].is_null_node = 0;
  if (x1 == x2 && y1 == y2) {
    tree[root].max = tree[root].min = p[x1][y1];
    return;
  }
  if (is_null_node) {
    tree[root].is_null_node = 1;
    return;
  }

  int xmid = (x1 + x2) >> 1;
  int ymid = (y1 + y2) >> 1;
  tree[root].son1 = ++cnt;
  tree[root].son2 = ++cnt;
  tree[root].son3 = ++cnt;
  tree[root].son4 = ++cnt;

  build(tree[root].son1, x1, y1, xmid, ymid, 0);
  build(tree[root].son2, x1, ymid+1, xmid, y2, ymid+1>y2);
  build(tree[root].son3, xmid+1, y1, x2, ymid, xmid+1>x2);
  build(tree[root].son4, xmid+1, ymid+1, x2, y2, xmid+1>x2||ymid+1>y2);
  update(root);
}

void change(int root, int x, int y, int c) {
  if (tree[root].is_null_node) return;
  if (x == tree[root].x1 && y == tree[root].y1 &&
      tree[root].x2 == x && tree[root].y2 == y) {
    tree[root].min = c;
    tree[root].max = c;
    return;
  } else if ( tree[root].x1 > x || tree[root].x2 < x ||
              tree[root].y1 > y || tree[root].y2 < y) {
    return;
  }
  change(tree[root].son1, x, y, c);
  change(tree[root].son2, x, y, c);
  change(tree[root].son3, x, y, c);
  change(tree[root].son4, x, y, c);
  update(root);
}

int64 query(int root, int x1, int y1, int x2, int y2, int type) {
  if ( (x1 <= tree[root].x1 && y1 <= tree[root].y1 &&
      tree[root].x2 <= x2 && tree[root].y2 <= y2) || tree[root].is_null_node) {
    if (type)
      return tree[root].min;
    return tree[root].max;
  } else if ( tree[root].x1 > x2 || tree[root].x2 < x1 ||
              tree[root].y1 > y2 || tree[root].y2 < y1) {
    if (type)
      return (int64) 10e15;
    return -1;
  }
  if (type) return min(
      min(
    query(tree[root].son1, x1, y1, x2, y2, type),
    query(tree[root].son2, x1, y1, x2, y2, type)
    ),
      min(
    query(tree[root].son3, x1, y1, x2, y2, type),
    query(tree[root].son4, x1, y1, x2, y2, type)
    )
    );
  return max(
      max(
    query(tree[root].son1, x1, y1, x2, y2, type),
    query(tree[root].son2, x1, y1, x2, y2, type)
    ),
      max(
    query(tree[root].son3, x1, y1, x2, y2, type),
    query(tree[root].son4, x1, y1, x2, y2, type)
    )
    );
}

void solve() {
  int m;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= n; ++ j) {
      scanf("%lld", p[i]+j);
    }
  }
  cnt = 1;
  build(1, 1, 1, n, n, 0);
  scanf("%d", &m);
  for (int i = 0; i < m; ++ i) {
    int a,b,l;
    scanf("%d %d %d", &a, &b, &l);
    int64 c = query(1, a-l/2, b-l/2, a+l/2, b+l/2, 0);
    //printf("%lld\n", c);
    c += query(1, a-l/2, b-l/2, a+l/2, b+l/2, 1);
    c /= 2;
    printf("%lld\n", c);
    change(1, a, b, c);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; ++ i) {
    printf("Case #%d:\n", i);
    solve();
  }

  return 0;
}

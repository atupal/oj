/*
   线段树，按高度排序，然后就是线段覆盖
   cover = 0 表示未覆盖
   cover = 1 表示部分被覆盖
   cover = 2 表示完全覆盖
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const long long maxn = 400100;
int n;
struct s{
  long long a;
  long long b;
  long long h;
} seg[maxn];

static struct {
  int left;
  int right;
  int cover;
} tree[maxn*3];

long long x[maxn<<1];

long long cmp(const s a, const s b) {
  return a.h > b.h or (a.h == b.h && a.b - a.a > b.b - b.a);
}

void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%lld %lld %lld", &seg[i].a, &seg[i].b, &seg[i].h);
    x[i<<1] = seg[i].a;
    x[i<<1|1] = seg[i].b;
  }
}


void build(int left, int right, int root) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].cover = 0;
  if (left+1==right) {
    return;
  }
  long long mid = (left + right) >> 1;
  build(left, mid, root<<1);
  build(mid, right, root<<1|1);
}

long long sum = 0;
void insert(long long left, long long right, long long h, long long root) {
  if (tree[root].cover == 2) return;
  if (left <= x[tree[root].left] and x[tree[root].right] <= right and tree[root].cover == 0) {
      sum += (x[tree[root].right] - x[tree[root].left]) * h;
      tree[root].cover = 2;
      return;
  } else if (left >= x[tree[root].right] or right <= x[tree[root].left]) {
    return;
  }
  insert(left, right, h, root<<1);
  insert(left, right, h, root<<1|1);
  /*
     这里记得update父节点，没有update 一直 tle。。。
   */
  if (tree[root<<1].cover == 2 and tree[root<<1|1].cover == 2) {
    tree[root].cover = 2;
  } else {
    tree[root].cover = 1;
  }
}

void solve() {
  sort(seg, seg+n, cmp);
  sort(x, x+(n<<1));
  int cnt;
  for (int i = 1, j = 1; j < (n<<1); ++ j, ++ i) {
    while (x[j] == x[j-1]) ++ j;
    x[i] = x[j];
    cnt = i;
  }
  build(0, cnt, 1);
  for (int i = 0; i < n; ++ i) {
    insert(seg[i].a, seg[i].b, seg[i].h, 1);
  }
  printf("%lld\n", sum);
}

int main() {
  input();
  solve();
  return 0;
}

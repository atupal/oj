/*
   线段树
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lson root<<1
#define rson root<<1|1

const int maxn = (65535<<1) + 3;

static struct {
    int left;
    int right;
    int cover;
    int mask;
} tree[maxn*4+11];

void build(int root, int left, int right) {
    tree[root].left = left;
    tree[root].right = right;
    tree[root].mask = 0;
    if (left >= right) {
      return;
    }
    int mid = (left + right) >> 1;
    build(lson, left, mid);
    build(rson, mid+1, right);
}

#define push(root)\
    if (c == 0) {\
    }\
    else if (c != 2 || tree[root].mask == 0) {\
      tree[root].mask = c;\
    } else {\
      if (tree[root].mask == 1) tree[root].mask = -1;\
      /* 下面两行忘了加 else 了,,,,结果就是上面一条语句执行完后继续执行下面的这条,, */\
      /* 查了好久... */\
      else if (tree[root].mask == -1) tree[root].mask = 1;\
      else if (tree[root].mask == 2) tree[root].mask = 0;\
    }\

void push_down(int root) {
  if (tree[root].left == tree[root].right) return;
  int c = tree[root].mask;
  push(lson);
  push(rson);
  tree[root].mask = 0;
}

void insert(int root, int left, int right, int c) {
  if (left <= tree[root].left && tree[root].right <= right) {
    push(root);
    return;
  } else if (left > tree[root].right || right < tree[root].left) {
    return;
  } 
  push_down(root);
  insert(lson, left, right, c);
  insert(rson, left, right, c);
}

int query(int val, int root) {
  if (tree[root].left == tree[root].right && tree[root].left == val) {
    if (tree[root].mask == 0) return 0;
    if (tree[root].mask == -1) return 0;
    if (tree[root].mask == 1) return 1;
    if (tree[root].mask == 2) return 1;
  }
  int mid = (tree[root].left + tree[root].right) >> 1;
  push_down(root);
  if (mid >= val) return query(val, lson);
  return query(val, rson);
}

void (*f[256]) (int root, int left, int right);
void U(int root, int left, int right) {
  insert(root, left, right, 1);
}
void I(int root, int left, int right) {
  insert(root, 0, left-1, -1);
  insert(root, right+1, maxn+1, -1);
}
void D(int root, int left, int right) {
  insert(root, left, right, -1);
}
void C(int root, int left, int right) {
  insert(root, 0, left-1, -1);
  insert(root, right+1, maxn+1, -1);
  insert(root, left, right, 2);
}
void S(int root, int left, int right) {
  insert(root, left, right, 2);
}

void out2();

void solve() {
    f['U'] = U, f['I'] = I, f['D'] = D, f['C'] = C, f['S'] = S;
    char oder, l, r;
    int a, b;
    build(1, 0, maxn+1);
    while (scanf("%c %c%d,%d%c\n", &oder, &l, &a, &b, &r) != EOF) {
        f[(int)oder](1, (a<<1)+(l=='('), (b<<1)-(r==')'));
    }
    out2();
}

int main() {
    solve();
    return 0;
}

void out2() {
  int flag=0;
  int i,j,lb,rb;
  for(i=0;i<=maxn+1;i++) {
    if (query(i,1)==0) continue;
    flag=1;
    lb=i;
    for(j=i+1;j<=maxn+1;j++){
      if (query(j,1)==0) break;
    }
    rb=j-1;
    if (lb&1) {printf("(%d,",lb/2);}
    else {printf("[%d,",lb/2);}
    if (rb&1) printf("%d)",(rb+1)/2);
    else printf("%d]",rb/2);
    printf(" ");
    i=j;
  }
  if (!flag) {
    printf("emp");
    printf("ty s");
    printf("et");
  }
}

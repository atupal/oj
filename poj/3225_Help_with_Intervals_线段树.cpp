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
    int lbd;
    int rbd;
    int cover;
    int mask;
    int flag;
} tree[maxn*4+11];

void build(int root, int left, int right) {
    tree[root].left = left;
    tree[root].right = right;
    tree[root].cover = 0;
    tree[root].mask = 0;
    tree[root].flag = 1;
    tree[root].lbd = left-1;
    tree[root].rbd = right+1;
    if (left >= right) {
      return;
    }
    int mid = (left + right) >> 1;
    build(lson, left, mid);
    build(rson, mid+1, right);
}

#define line(x)\
  if (c == 1) {\
    x = 1;\
  } else if (c == -1) {\
    x = 0;\
  } else if (c == 2) {\
    x = not x;\
  }\

void push_down(int root) {
  int c = tree[root].mask;
  if (c) {
    tree[lson].cover = tree[root].cover;
    tree[rson].cover = tree[root].cover;
    tree[lson].mask = c;
    tree[rson].mask = c;
    if (tree[root].cover) {
      tree[lson].lbd = tree[lson].right;
      tree[lson].rbd = tree[lson].left;
      tree[rson].lbd = tree[rson].right;
      tree[rson].rbd = tree[rson].left;
    } else {
      tree[lson].lbd = -1; 
      tree[lson].rbd = -1; 
      tree[rson].lbd = -1; 
      tree[rson].rbd = -1; 
    }
    tree[lson].flag = 1;
    tree[rson].flag = 1;
    tree[root].mask = 0;
  }
}

void update(int root) {
  if (tree[lson].cover == tree[rson].cover and tree[lson].flag and tree[rson].flag) {
    tree[root].cover = tree[lson].cover;
    tree[root].flag = 1;
  } else {
    tree[root].flag = 0;
  }

  tree[root].lbd = tree[lson].lbd;
  if (tree[rson].lbd != -1 and tree[lson].lbd == tree[lson].right) {
    tree[root].lbd = tree[rson].lbd;
  }
  tree[root].rbd = tree[rson].rbd;
  if (tree[lson].rbd != -1 and tree[rson].rbd == tree[rson].left) {
    tree[root].rbd = tree[lson].rbd;
  }
}

void insert(int root, int left, int right, int c) {
  tree[root].flag = 0;
  if (left <= tree[root].left and tree[root].right <= right) {
    line(tree[root].cover);
    tree[root].mask = c;
    tree[root].flag = 1;
    if (tree[root].cover) {
      tree[root].lbd = tree[root].right;
      tree[root].rbd = tree[root].left;
    } else {
      tree[root].lbd = -1;
      tree[root].rbd = -1;
    }
    return;
  } else if (left > tree[root].right or right < tree[root].left) {
    return;
  } 
  push_down(root);
  insert(lson, left, right, c);
  insert(rson, left, right, c);
  update(root);
}

void (*f[256]) (int root, int left, int right);
void U(int root, int left, int right) {
  insert(root, left, right, 1);
}
void I(int root, int left, int right) {
  insert(root, -1, left-1, -1);
  insert(root, right+1, maxn+1, -1);
}
void D(int root, int left, int right) {
  insert(root, left, right, -1);
}
void C(int root, int left, int right) {
  insert(root, -1, left-1, -1);
  insert(root, right+1, maxn+1, -1);
  insert(root, left, right, 2);
}
void S(int root, int left, int right) {
  insert(root, left, right, 2);
}

void query(int root) {
  if (tree[root].left == tree[root].right) {
    return;
  }
  query(lson);

  l = tree[lson].rbd;

  query(rson);
}

void solve() {
    f['U'] = U, f['I'] = I, f['D'] = D, f['C'] = C, f['S'] = S;
    char order, l, r;
    int a, b;
    build(1, -1, maxn+1);
    while (scanf("%c %c%d,%d%c\n", &order, &l, &a, &b, &r) != EOF) {
        //printf("%c %c%d,%d%c\n", order, l, a,b,r);
        f[(int)order](1, (a<<1)+(l=='('), (b<<1)-(r==')'));
    }
    query(1);
}

int main() {
    solve();
    return 0;
}

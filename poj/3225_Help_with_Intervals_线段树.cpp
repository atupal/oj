/*
   线段树
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lson root<<1
#define rson root<<1|1

const int maxn = 65535;

static struct {
    int left;
    int right;
    int lbd;
    int cover;
    int mask;
} tree[maxn*3+11];

void build(int root, int left, int right) {
    tree[root].left = left;
    tree[root].right = right;
    tree[root].lbd = 0;
    tree[root].cover = 0;
    tree[root].mask = 0;
    if (left == right-1) {
        return;
    }
    int mid = (left + right) >> 1;
    build(lson, left, mid);
    build(rson, mid, right);
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
      tree[lson].lbd = tree[root].lbd;
      tree[rson].lbd = tree[root].cover;
      tree[lson].mask = c;
      tree[rson].mask = c;
      tree[root].mask = 0;
    }
}

void update(int root) {
}

void insert(int root, int left, int right, int l, int r, int c) {
  int flag = 0;
  if ( (l and left == tree[root].left and left != right)
        or (r and right == tree[root].left and left != right)
        or (l and r and left == right and left == tree[root].left)) {
    line(tree[root].lbd);
    flag = 1;
  }

  if (left <= tree[root].left and tree[root].right <= right) {
    line(tree[root].cover);
    if (left != tree[root].left) {
      line(tree[root].lbd);
    }
    tree[root].mask = c;
    if (flag) {
      return;
    }
  }
  if (left >= tree[root].right or right < tree[root].left or (right == tree[root].left and not r)) {
    return;
  } 
  if (tree[root].left+1 == tree[root].right) {
    return;
  }
  push_down(root);
  insert(lson, left, right, l, r, c);
  insert(rson, left, right, l, r, c);
  update(root);
}

void query(int root, int left, int right) {
  if (left >= tree[root].right or right <= tree[root].left ) {
    return;
  }
  push_down(root);
  if (tree[root].left+1 == tree[root].right) {
    if (tree[root].cover) {
      if (tree[root].lbd) {
        printf("[%d,%d)", tree[root].left, tree[root].right);
      } else {
        printf("(%d,%d)", tree[root].left, tree[root].right);
      }
    } else if (tree[root].lbd) {
      printf("[%d,%d] ", tree[root].left, tree[root].left);
    }
  } else {
    query(lson, left, right);
    query(rson, left, right);
  }
}

void (*f[256]) (int root, int left, int right, int a, int b);
void U(int root, int left, int right, int a, int b) {
  insert(root, left, right, a, b, 1);
}
void I(int root, int left, int right, int a, int b) {
  insert(root, 1, left, 1, not b, -1);
  insert(root, left, maxn, not a, 1, -1);
}
void D(int root, int left, int right, int a, int b) {
  insert(root, left, right, a, b, -1);
}
void C(int root, int left, int right, int a, int b) {
  insert(root, 1, left, 1, not b, -1);
  insert(root, left, maxn, not a, 1, -1);
  insert(root, left, right, a, b, 2);
}
void S(int root, int left, int right, int a, int b) {
  insert(root, left, right, a, b, 2);
}

void solve() {
    f['U'] = U, f['I'] = I, f['D'] = D, f['C'] = C, f['S'] = S;
    char order, l, r;
    int a, b;
    build(1, 0, maxn+1);
    while (scanf("%c %c%d,%d%c\n", &order, &l, &a, &b, &r) != EOF) {
        //int left = 0, right = 0;
        f[(int)order](1, a, b, l=='[', r==']');
        printf("%c %c%d,%d%c\n", order, l, a,b,r);
        query(1, 0, 10);
        printf("\n");
    }
    //query(1, 0, 10);
}

int main() {
    solve();
    return 0;
}

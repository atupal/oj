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
    int flag;
} tree[maxn*3+11];

void build(int root, int left, int right) {
    tree[root].left = left;
    tree[root].right = right;
    tree[root].lbd = 0;
    tree[root].cover = 0;
    tree[root].mask = 0;
    tree[root].flag = 0;
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
      //tree[lson].cover = tree[root].cover;
      //tree[rson].cover = tree[root].cover;
      //tree[lson].lbd = tree[root].lbd;
      //tree[rson].lbd = tree[root].cover;
      line(tree[lson].cover);
      line(tree[rson].cover);
      line(tree[lson].lbd);
      line(tree[rson].lbd);
      tree[lson].mask = c;
      tree[rson].mask = c;
      tree[root].mask = 0;
    }
}

void update(int root) {
  if (tree[lson].cover == tree[rson].cover 
      and tree[lson].cover == tree[rson].lbd) {
    tree[root].flag = 1;
    tree[root].cover = tree[lson].cover;
  } else {
    tree[root].flag = 0;
  }
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
      if (left == 2 and right == 4) {
        //printf("debug:<%d, %d>\n", tree[root].left, tree[root].right);
      }
    if (left != tree[root].left) {
      line(tree[root].lbd);
    }
    tree[root].mask = c;
    tree[root].flag = 1;
    if (not flag or 1) {
      //return;
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
  //update(root);
}

static struct {
  int left;
  int cover;
} ans[maxn+3];

void query(int root, int left, int right) {
  if (tree[root].left+1 == tree[root].right) {
    if (tree[root].cover) {
      if (tree[root].lbd) {
        //printf("[%d,%d)", tree[root].left, tree[root].right);
        ans[tree[root].left].cover = 1;
        ans[tree[root].left].left = 1;
      } else {
        //printf("(%d,%d)", tree[root].left, tree[root].right);
        ans[tree[root].left].cover = 1;
        ans[tree[root].left].left = 0;
      }
    } else if (tree[root].lbd) {
      //printf("[%d,%d] ", tree[root].left, tree[root].left);
      ans[tree[root].left].cover = 0;
      ans[tree[root].left].left = 1;
    }
  } else {
    push_down(root);
    query(lson, left, right);
    query(rson, left, right);
  }
}

void (*f[256]) (int root, int left, int right, int a, int b);
void U(int root, int left, int right, int a, int b) {
  insert(root, left, right, a, b, 1);
}
void I(int root, int left, int right, int a, int b) {
  insert(root, 0, left, 1, not a, -1);
  insert(root, right, maxn, not b, 1, -1);
}
void D(int root, int left, int right, int a, int b) {
  insert(root, left, right, a, b, -1);
}
void C(int root, int left, int right, int a, int b) {
  insert(root, 0, left, 1, not a, -1);
  insert(root, right, maxn, not b, 1, -1);
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
        //printf("%c %c%d,%d%c\n", order, l, a,b,r);
        f[(int)order](1, a, b, l=='[', r==']');
        //query(1, 0, 10);
        //printf("\n");
    }
    query(1, 0, maxn);
    //printf("\n");
}

int main() {
    solve();
    int l = 0;
    while (l<maxn+3) {
      if (ans[l].left) {
        printf("[%d,", l);
      } else if (ans[l].cover) {
        printf("(%d,", l);
      } else {
        ++ l;
        continue;
      }

      while (l<maxn+3) {
        if (not ans[l].cover) {
          if (ans[l].left) {
            printf("%d] ", l);
          } else {
            printf("%d) ", l);
          }
          ++ l;
          break;
        }
        ++ l;
      }
    }
    return 0;
}

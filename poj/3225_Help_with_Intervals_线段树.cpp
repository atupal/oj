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
    int rbd;
    int cover;
    int mask;
} tree[maxn*3+11];

void build(int root, int left, int right) {
    tree[root].left = left;
    tree[root].right = right;
    tree[root].lbd = 0;
    tree[root].rbd = 0;
    tree[root].cover = 0;
    tree[root].mask = 0;
    if (left == right-1) {
        return;
    }
    int mid = (left + right) >> 1;
    build(lson, left, mid);
    build(rson, mid, right);
}

#define line(x) \
        if (tree[x].cover + c >= 0) {\
            tree[x].cover += c;\
        }\
        tree[x].lbd = tree[x].cover;\
        tree[x].rbd = tree[x].cover;\
        tree[x].mask = c;\

void push_down(int root) {
    int c = tree[root].mask;
    if (c) {
        line(lson);
        line(rson);
    }
}

void update(int root) {
}

void insert(int root, int left, int right, int a, int b, int c) {
    if (left < tree[root].left and tree[root].right < right) {
        line(root);
        return;
    }
    if (left == tree[root].left and a) {
        tree[root].lbd = 1;
    }
    if (right == tree[root].right and b) {
        tree[root].rbd = 1;
    }
    if (left >= tree[root].right or right <= tree[root].left) {
        return;
    }
    push_down(root);
    insert(lson, left, right, a, b, c);
    insert(rson, left, right, a, b, c);
    update(root);
}

void del(int root, int left, int right) {
}

void (*f[256]) (int root, int left, int right);
void U(int root, int left, int right) {
}
void I(int root, int left, int right) {
}
void D(int root, int left, int right) {
}
void C(int root, int left, int right) {
}
void S(int root, int left, int right) {
}

void solve() {
    f['U'] = U, f['I'] = I, f['D'] = D, f['C'] = C, f['S'] = S;
    char order, l, r;
    int a, b;
    build(1, 0, maxn);
    while (scanf("%c %c%d,%d%c\n", &order, &l, &a, &b, &r) != EOF) {
        int left = 0, right = 0;
        f[(int)order](1, left, right);
    }
}

int main() {
    solve();
    return 0;
}

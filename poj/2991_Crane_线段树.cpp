/*
   trans(a, x, y) 表示以 x,y 为中心逆时针旋转 a ° 的矩阵变换.
   假设绕原点的旋转矩阵为 A, 则 trans = A + (x, y) - (x, y)A
   tree[root] 表示 第 left 段 seg 到 第 right 段 seg 的首尾坐标, mask 表示这段线段经历的变换
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define lson (root<<1)
#define rson (root<<1|1)

const double PI = 3.141592653589793;

const int maxn = 100100;
int l[maxn];
int n, c;
int angle[maxn];
double cache_sin[360];
double cache_cos[360];
#define c_sin(a) (cache_sin[a] == 1024. ? cache_sin[a] = sin(a/360.*2*PI) : cache_sin[a])
#define c_cos(a) (cache_cos[a] == 1024. ? cache_cos[a] = cos(a/360.*2*PI) : cache_cos[a])

struct trans {
  double matrix[2][2];
  double x0, y0;
  trans (const trans &t) {
    memcpy(matrix, t.matrix, sizeof(double)*4);
    x0 = t.x0;
    y0 = t.y0;
  }
  /*
    angle trans matrx:
    m[0][0], m[0][1]
    m[1][0], m[1][1]

    cos,  sin
    -sin, cos
   */

  trans () {
    matrix[0][0] = 1., matrix[0][1] = 0.;
    matrix[1][0] = 0., matrix[1][1] = 1.;
    x0 = 0.;
    y0 = 0.;
  }

  int is_empty() {
    return matrix[0][0] == 1. && matrix[0][1] == 0. && 
            matrix[1][0] == 0. && matrix[1][1] == 1. &&
            x0 == 0. && y0 == 0.;
  }

  trans (int angle, double x, double y) {
    //angle %= 360;
    //double a = (angle / 360.) * 2 * PI;
    int a = (angle+360) % 360;
    matrix[0][0] = c_cos(a), matrix[0][1] = c_sin(a);
    matrix[1][0] = -matrix[0][1], matrix[1][1] = matrix[0][0];
    x0 = x - matrix[0][0] * x - matrix[1][0] * y;
    y0 = y - matrix[0][1] * x - matrix[1][1] * y;
  }

  trans operator + (const trans &t2) {
    trans new_t;

    new_t.matrix[0][0] = matrix[0][0] * t2.matrix[0][0] + matrix[0][1] * t2.matrix[1][0];
    new_t.matrix[0][1] = matrix[0][0] * t2.matrix[0][1] + matrix[0][1] * t2.matrix[1][1];
    new_t.matrix[1][0] = matrix[1][0] * t2.matrix[0][0] + matrix[1][1] * t2.matrix[1][0];
    new_t.matrix[1][1] = matrix[1][0] * t2.matrix[0][1] + matrix[1][1] * t2.matrix[1][1];

    new_t.x0 = t2.x0 + t2.matrix[0][0] * x0 + t2.matrix[1][0] * y0;
    new_t.y0 = t2.y0 + t2.matrix[0][1] * x0 + t2.matrix[1][1] * y0;
    return new_t;
  }
  trans operator += (const trans &t2) {
    *this = *this + t2;
    return *this;
  }
  trans operator = (const trans &t2) {
    memcpy(matrix, t2.matrix, sizeof(double)*4);
    x0 = t2.x0;
    y0 = t2.y0;
    return *this;
  };
  void print() {
    printf("%.2lf %.2lf\n%.2lf %.2lf\n", matrix[0][0], matrix[0][1],
                                         matrix[1][0], matrix[1][1]);
    printf("%.2lf %.2lf\n", x0, y0);
  };
};

struct vector {
  double x, y;
  vector() {
    x = 0.;
    y = 0.;
  }
  vector(double x, double y) {
    this->x = x;
    this->y = y;
  };
  vector(const vector &v) {
    x = v.x;
    y = v.y;
  }
  void set(double x, double y) {
    this->x = x;
    this->y = y;
  }
  vector operator * (trans t) {
    vector new_v;
    new_v.x = t.x0 + t.matrix[0][0] * x + t.matrix[1][0] * y;
    new_v.y = t.y0 + t.matrix[0][1] * x + t.matrix[1][1] * y;
    return new_v;
  }
  vector operator *= (const trans t) {
    *this = *this * t;
    return *this;
  }
  vector operator = (const vector v) {
    x = v.x;
    y = v.y;
    return *this;
  };
};

static struct {
  int left, right;
  vector b, e;
  trans mask;
} tree[maxn*3+1];

void build(int root, int left, int right) {
  tree[root].left = left;
  tree[root].right = right;
  tree[root].b.set(0, (double) l[left-1]);
  tree[root].e.set(0, (double) l[right]);
  tree[root].mask = trans();
  if (left == right) {
    return;
  }
  int mid = (left + right) >> 1;
  build(lson, left, mid);
  build(rson, mid+1, right);
}

#define push(root) \
    tree[root].b *= t;\
    tree[root].e *= t;\
    tree[root].mask += t;\

void push_down(int root) {
  if (tree[root].left == tree[root].right) {
  } else if (!tree[root].mask.is_empty()) {
    trans t = tree[root].mask;
    push(lson);
    push(rson);
    tree[root].mask = trans();
  }
}

void update(int root) {
  tree[root].b = tree[lson].b;
  tree[root].e = tree[rson].e;
}

void insert(int root, int left, int right, trans t) {
  if (left <= tree[root].left && tree[root].right <= right) {
    push(root);
    return;
  } else if (tree[root].left > right || tree[root].right < left) {
    return;
  }
  push_down(root);
  insert(lson, left, right, t);
  insert(rson, left, right, t);
  update(root);
}

vector query(int root, int val) {
  if (tree[root].right == val) {
    return tree[root].e;
  } else {
    push_down(root);
    int mid = (tree[root].left + tree[root].right) >> 1;
    if (mid < val) {
      return query(rson, val);
    } else {
      return query(lson, val);
    }
  }
}

void solve() {
  int s, a;
  vector O(0, l[n]);
  build(1, 1, n);
  for (int i = 0; i < c; ++ i) {
    scanf("%d %d", &s, &a);
    vector v = query(1, s);
    trans t = trans(a-angle[s], v.x, v.y);
    //printf("xy;%.2lf %.2lf\n", v.x, v.y);
    //t.print();
    angle[s] = a;
    insert(1, s+1, n, t);
    O *= t;
    //O = query(1, n);
    printf("%.2lf %.2lf\n", O.x, O.y);
  }
  printf("\n");
}

int main() {
  for (int i = 0; i < 360; ++ i) {
    cache_sin[i] = cache_cos[i] = 1024.;
  }
  while (scanf("%d %d", &n, &c) != EOF) {
    l[0] = 0;
    for (int i = 1; i <= n; ++ i) {
      scanf("%d", l+i);
      l[i] += l[i-1];
      angle[i] = 180;
    }
    solve();
  }

  return 0;
}


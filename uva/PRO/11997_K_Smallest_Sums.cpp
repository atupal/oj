#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 760;

struct node {
  int x;
  int y;

  node(int a, int b) {
    x = a;
    y = b;
  };
  
  bool operator < (const node & a) const {
    return x > a.x;
  };
};

int A[maxn][maxn];

void merge(int *a, int *b, int n) {
  piority_queue<node> pq;
  for (int i = 0; i < n; ++ i) {
    pq.push(node(a[i] + b[0], 0));
  }
  for (int i = 0; i< n; ++ i) {
    node tmp = pq.top(); pq.pop();
    a[i] = tmp.x;
    if (tmp.y + 1 < n) {
    }
  }
}

int main() {
  int n;
  while (scanf("%d", &n) != EOF) {
    for (int i = 0; i < n; ++ i) {
      for (int j = 0; j < n; ++ j) {
        scanf("%d", A[i] + j);
      }
      sort(A[i], A[i] + n);
    }
    for (int i = 0; i < n - 1; ++ i) {
      merge(A[0], A[i + 1], n);
    }

    for (int i = 0; i < n - 1; ++ i) {
      printf("%d ", A[0][i]);
    }
    printf("%d\n", A[0][n - 1]);
  }
}

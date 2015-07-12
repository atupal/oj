#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;

typedef long long int64;
typedef long long ll;
const int64 MOD = (int64) 1e9+7;
const int maxn = 90001;
int n;
double A[1001][1001];
int x[1001];
map<int, ll> cache;


int gcd(int a, int b) {
  while (a && b) b%=a^=b^=a^=b;
  return a+b;
}

void swap_col(int x, int y, int n) {
  if (x == y) return;
  for (int i = 0; i < n; ++ i) {
    //A[i][x] ^= A[i][y] ^= A[i][x] ^= A[i][y];
    double tmp = A[i][x];
    A[i][x] = A[i][y];
    A[i][y] = tmp;
  }
}

int get_nonzero_col(int row, int n) {
  for (int i = 0; i < n; ++ i) {
    if (A[row][i]) return i;
  }

  return n;
}

void minus_row(int x, int y, double c, int n) {
  for (int i = 0; i < n; ++ i) {
    A[x][i] -= A[y][i] * c;
  }
}

int64 guass(int n) {
  int col = 0;
  int64 ans = 1;
  for (int row = 0; row < n; ++ row) {
    int nonzero = get_nonzero_col(row, n);
    if (nonzero == n) {
      return 0;
    }
    swap_col(nonzero, col, n);
    for (int i = row+1; i < n; ++ i) {
      minus_row(i, row, A[i][col]/A[row][col], n);
    }
    ans *= A[row][col];
    ans %= MOD;
    col ++;
  }

  return ans;
}

inline
ll euler(ll n) {
  ll ret = n;
  ll bd = (ll)sqrt((double)n) + 1;
  if (bd >= n) bd = n-1;
  for (ll i = 2; i <= bd; ++ i ) {
    if (n%i == 0) {
      ret *= (i-1);
      ret /= i;
      while (n%i==0) {
        n /= i;
      }
    }
  }
  if (n > 1) {
    ret *= (n-1);
    ret /= n;
  }

  return ret;
}


/*
 * 首先, x1,,,xn 的顺序无所谓, 不影响行列式的结果.
 * 所以对 x1,...xn 按小到大排序, 比如说 1,3,9,27, 不同的约数链是互不影响的,
 * 因为两两互质, 在矩阵中相应的元素为 1 ,用 第一行 1 去减的时候都为 0了.
 *
 * 然后我们发现,要求第 n 个数的最后在矩阵化为的上三角形时的在对角线的值是啥时,
 * 我们发现在 xn 的约数链对应的那些行上, 对角线上的值和最后一列的值是一样的,
 * 所以假设 xi 最后在上三角矩阵上对角线上的值为 f(xi), 则有 f(xn) = n-sum{f(xd) | xd 整除 xn}
 * 最后的行列式的结果便等于上三角的对角线的乘积, 即f(x1)*f(x2)*f(x3)...f(xn) 
 * f(xi) 的值直接从 x1 递推到 xn 就可以得到. 其实这也就是欧拉函数.
 *
 * */
void solve() {
  /*
  printf("%lld\n", guass(n));
  */


  sort(x, x+n);
  ll ans = 1;
  for (int i = 0; i < n; ++ i) {

    ll phi = x[i];

    for (int j = 0; j < i; ++ j) {
      if (x[i]%x[j] == 0) {
        phi -= cache[x[j]];
      }
    }

    cache[x[i]] = phi;

    ans *= phi;
    ans %= MOD;
  }

  printf("%lld\n", ans);
}


int main() {

  while (scanf("%d", &n) != EOF) {
    for (int i = 0; i < n; ++ i) {
      scanf("%d", x+i);
    }

    /*
    for (int i = 0; i < n; ++ i) {
      for (int j = i; j < n; ++ j) {
        A[i][j] = A[j][i] = (double)gcd(x[i], x[j]);
      }
    }
    */

    solve();
  }

  return 0;
}


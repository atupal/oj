#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <vector>
#define MAXN 100010
#define _cp(a,b) ((a)<=(b))
using namespace std;

typedef int elem_t;
typedef long long ll;
elem_t _tmp[MAXN];

ll inv(int n,elem_t* a) {
  int l=n>>1,r=n-l,i,j;
  ll ret=(r>1?(inv(l,a)+inv(r,a+l)):0);
  for (i=j=0;i<=l;_tmp[i+j]=a[i],i++)
    for (ret+=(ll)j;j<r&&(i==l||!_cp(a[i],a[l+j]));_tmp[i+j]=a[l+j],j++);
  memcpy(a,_tmp,sizeof(elem_t)*n);
  return ret;
}

int n, k;
int a[MAXN];
int b[MAXN];

int p[][3] = {
  {1,2,3},
  {1,3,2},
  {2,1,3},
  {2,3,1},
  {3,1,2},
  {3,2,1}
};

void solve() {
  ll ans = (ll)MAXN*(ll)MAXN, tmp;
  if (k == 1) {
    printf("0\n");
    return;
  }
  if (k == 2) {
    for (int i = 0; i < n; ++ i) {
      if (a[i] == 1) b[i] = 1;
      if (a[i] == 2) b[i] = 2;
    }
    tmp = inv(n, b);
    if (tmp < ans) ans = tmp;
    for (int i = 0; i < n; ++ i) {
      if (a[i] == 1) b[i] = 2;
      if (a[i] == 2) b[i] = 1;
    }
    tmp = inv(n, b);
    if (tmp < ans) ans = tmp;

    printf("%lld\n", ans);
    return;
  }

  for (int t = 0; t < 6; ++ t) {
    for (int i = 0; i < n; ++ i) {
      if (a[i] == 1) b[i] = p[t][0];
      if (a[i] == 2) b[i] = p[t][1];
      if (a[i] == 3) b[i] = p[t][2];
    }
    tmp = inv(n, b);
    if (tmp < ans) ans = tmp;
  }

  printf("%lld\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++ cas) {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++ i) scanf("%d", a+i);
    printf("Case #%d: ", cas);
    solve();
  }

  return 0;
}


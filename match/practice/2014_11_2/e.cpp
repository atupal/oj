#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef long long int64;

int64 n ,d;

int get(int k) {
  int cnt = 0;
  int64 nn = n;
  while (nn) {
    if (nn%k==d) ++cnt;
    else break;
    nn /= k;
  }
  return cnt;
}

int max= 0;
int64 ans = 2;
void solve()  {
  int u = (int) sqrt(n) + 1;

  for (int k = 2; k <= u; ++ k) {
    int t = get(k);
    if (t > max) {
      max = t;
      ans = k;
    }
  }

  if (max < 1 && n -d >= 0) {
    u = (int) sqrt(n-d+1);
    int i;
    for (i = u-1; i>0; -- i) {
      if ( (n-d) % i == 0 && (n-d)/i > d) {
        ans = (n-d)/i;
        max = 1;
        break;
      }
    }

    if (n==d) {
      ans = d+1;
      max = 1;
    }
  }

  if (d && max < 2 && n -d >= 0) {
    if ((n-d)%d==0 && d < (n-d)/d) {
      max = 2;
      ans = (n-d)/d;
    }
  }
}

int main() {
  scanf("%I64d %I64d", &n, &d);

  if (n+d==0) {
    printf("2 1");
    return 0;
  }


  solve();


  //for (int i = 1; i < 100; ++ i) {
  //  for (int j = 0; j < 10; ++ j) {
  //    n = i;
  //    d = j;
  //    max = 0;
  //    ans = 2;
  //    solve();

  //    int aa = 2, mm = 0;

  //    for (int k = 2; k <= i+1; ++ k) {
  //      int t= get(k);
  //      if (t > mm) {
  //        mm = t;
  //        aa = k;
  //      }
  //    }

  //    if (ans != aa) {
  //      printf("%d %d: (%d, %d) (%I64d %d)\n",i, j, aa, mm , ans, max);
  //    }
  //  }
  //}


  printf("%I64d %d\n", ans, max);

  return 0;
}

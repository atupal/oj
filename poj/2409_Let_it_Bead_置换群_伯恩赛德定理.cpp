/*
   对于旋转置换群，群内置换的总个数显而易见是n个（转n次就返回到自己了嘛），第i个置换中循环节的个数可以用dfs搜索出来，不过有直接的结论，循环节个数应该是gcd(n,i)个，这个结论所有博客都给出了，但是几乎都没给证明（大神都觉得太显而易见了吧）。

   对于翻转置换，看上面的那个图，它已经给了你很大提示，找循环节的关键是找对称轴。这里n要分奇偶性。

   当n为奇数，那么对称轴就是每个点和圆心的连线，共n条（观察第二个图），那么显然除了这个点没变，其他的点都跟对称的那个点置换了，所以循环节的个数是（n-1）/2+1。

   当n为偶数，那么对称轴有每个点和对面的点的连线，共n/2条，显然除了对称轴上的两个点，其余点都跟对面的点置换了循环节的个数是(n-2)/2+2，两个相邻点中点和圆心的连线也是n/2条，显然每个点都跟对面的点置换了，循环节的个数是n/2，n为偶也是n条对称轴，
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int n, c;

typedef long long int64;

int64 gcd(int64 a, int64 b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

void solve () {
  if (n == 0) {
    printf("0\n");
    return;
  }
  int64 sum = 0; 
  for (int i = 0; i < n; ++ i) {
    sum += (int64) pow(c, gcd(n, i) * 1.0);
  }
  if (n&1)
    sum += (int64) pow(c, (n+1)/2*1.0) * n;
  else
    sum += (int64) pow(c, (n-2)/2+2.0) * n/2 + (int64) pow(c, n/2.0) * n/2;
  sum /= n*2;
  printf("%lld\n", sum);
}

int main() {
  for (;;) {
    scanf("%d %d", &c, &n);
    if (n+c==0) break;
    solve();
  }

  return 0;
}

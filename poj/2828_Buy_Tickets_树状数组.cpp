/*
   树状数组
   先把输入数据存下来，然后倒着插进去，插到当前位置后的第一个为空的位子就好了
   用树状数组保存空位的个数和
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lowbit(a) (a&(-a))

const int maxn = 200010;
int bit[maxn];
int ans[maxn];
int pos[maxn];
int val[maxn];
int n;

void modify(int p, int delta) {
  while (p <= n) {
    bit[p] += delta;
    p += lowbit(p);
  }
}

/*
int sum(int p) {
  int ret = 0;
  while (p) {
    ret += bit[p];
    p -= lowbit(p);
  }

  return ret;
}
*/

//寻找部分和为k的第一个位置 
int sumseek(int k) {
  int ans = 0, sum = 0;
  for (int i = 18; i >= 0; i--)
  {
    ans += (1 << i);
    if (ans >= n || sum + bit[ans] >= k) ans -= (1 << i);
    else sum += bit[ans];
  }
  return ans + 1;
}


int input_and_init() {
  if (scanf("%d", &n) == EOF) return 0;

  for (int i = 1; i <= n; ++ i) {
    bit[i] = lowbit(i);
    scanf("%d %d", pos+i, val+i);
    ++ pos[i];
  }
  return 1;
}

void solve() {
  for (int i = n; i; -- i) {
    int ind = sumseek(pos[i]);
    ans[ind] = val[i];
    modify(ind, -1);
  }
  for (int i = 1; i < n; ++ i) 
    printf("%d ", ans[i]);
  printf("%d\n", ans[n]);
}
  
int main() {
  while (input_and_init()) {
    solve();
  }

  return 0;
}

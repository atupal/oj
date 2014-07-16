/*
   记录当前位置是否有人，没人为0，有人为1
   让第n 个人出圈时只要部分和为 n 的位置就可以了
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lowbit(x) (x&(-x))
#define abs(a) ((a) > 0 ? (a) : (-(a)))

const int maxn = 500010;
int n,k;
int bit[maxn];

int antprime[] = {1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,
  5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960, 999999999};
int candynumber[] = {1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200};

struct child {
  char name[11];
  int num;
} children[maxn];

int getprime() {
  int i;
  for (i = 0; antprime[i] <= n; ++ i);
  return i - 1;
}

void modify(int x, int delta) {
  while (x <= n) {
    bit[x] += delta;
    x += lowbit(x);
  }
}

int sum(int x) {
  int ans = 0;
  while (x) {
    ans += bit[x];
    x -= lowbit(x);
  }
  return ans;
}

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

void solve() {
  for (int i = 1; i <= n; ++ i) {
    bit[i] = lowbit(i);
  }
  int out = k, t, cnt = n, left;
  int prime = getprime();
  for (int i = 1; i <= n; ++ i) {
    //printf("%s\n", children[out].name);
    if (i == antprime[prime]) break;
    modify(out, -1);
    -- cnt;
    // 这里 num 的绝对值可能小于 cnt，所以只加上 cnt 是不够的，因为这个 wa 了好久。。。
    t = (children[out].num + cnt * (abs(children[out].num)/cnt+1)) % cnt;
    t = t == 0 ? cnt : t;
    left = sum(out);
    if (cnt - left >= t) {
      out = sumseek(left + t);
    } else {
      out = sumseek(t - (cnt - left));
    }
  }
  printf("%s %d\n", children[out].name, candynumber[prime]);
}

int input() {
  if (scanf("%d %d", &n, &k) == EOF) return 0;
  for (int i = 1; i <= n; ++ i) {
    scanf("%s %d", children[i].name, &children[i].num);
    if (children[i].num < 0) {
      children[i].num += 1;
    }
  }
  return 1;
}

int main() {
  while (input()) solve();
  return 0;
}

/*
 * 单调队列优化
 * http://www.cnblogs.com/kedebug/archive/2013/04/06/3002882.html
 * http://blog.csdn.net/iaccepted/article/details/6699691
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 10010;
int N;
int S;

int dp[maxn];
int sumT[maxn];
int sumF[maxn];
int q[maxn];

void input() {
  scanf("%d", &N);
  scanf("%d", &S);
  for (int i = 1; i <= N; ++ i) {
    scanf("%d %d", sumT+i, sumF+i);
  }
  for (int i = N-1; i; --i ) {
    sumT[i] += sumT[i+1];
    sumF[i] += sumF[i+1];
  }
}

inline
double slope(int i, int j) {
  return 1. * (dp[i]-dp[j])/(sumT[i]-sumT[j]);
}

void solve() {
  int head = 0;
  int tail = -1;
  dp[N+1]=0;
  q[++tail] = N+1;
  for (int i=N; i; --i ) {
    while (head < tail and slope(q[head], q[head+1]) <= (double)sumF[i]) {
      ++ head;
    }
    int j = q[head];
    dp[i] = dp[j] - sumF[i] * sumT[j] + (S + sumT[i]) * sumF[i];
    while (head < tail and slope(q[tail], q[tail-1]) >= slope(i,q[tail])) {
      --tail;
    }
    q[++tail]=i;
  }

  printf("%d\n", dp[1]);
}

int main() {
  input();
  solve();

  return 0;
}

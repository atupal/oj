/*
   单调队列
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 1000010;

int n, k;

int dq_max[maxn];
int l_max, r_max;
int dq_min[maxn];
int l_min, r_min;

int s[maxn];
int s1[maxn];
int s2[maxn];

/*
inline
void insert(int ind) {
  int low, high, mid;

  low = l_max;
  high = r_max;
  while (low <= high) {
    mid = (low + high) >> 1;
    if (s[dq_max[mid]] > s[ind]) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  r_max = ++ high;
  dq_max[r_max] = ind;

  low = l_min;
  high = r_min;
  while (low <= high) {
    mid = (low + high) >> 1;
    if (s[dq_min[mid]] < s[ind]) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  r_min = ++ high;
  dq_min[r_min] = ind;
}
*/

void solve() {
  scanf("%d %d", &n, &k);
  l_max = 0, r_max = -1;
  l_min = 0, r_min = -1;
  for (int i = 0; i < n; ++ i) {
    scanf("%d", s+i);
  }

  for (int i = 0; i < n; ++ i) {
    //insert(i);
    int ind = i;
  int low, high, mid;

  low = l_max;
  high = r_max;
  while (low <= high) {
    mid = (low + high) >> 1;
    if (s[dq_max[mid]] > s[ind]) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  r_max = ++ high;
  dq_max[r_max] = ind;

  low = l_min;
  high = r_min;
  while (low <= high) {
    mid = (low + high) >> 1;
    if (s[dq_min[mid]] < s[ind]) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  r_min = ++ high;
  dq_min[r_min] = ind;
    if (i >= k-1) {
      s1[i] = s[dq_max[l_max]];
      s2[i] = s[dq_min[l_min]];
    }
    if (i - dq_max[l_max] >= k-1) ++ l_max;
    if (i - dq_min[l_min] >= k-1) ++ l_min;
  }

  for (int i = k-1; i < n; ++ i) {
    printf("%d ", s2[i]);
  }
  printf("\n");
  for (int i = k-1; i < n; ++ i) {
    printf("%d ", s1[i]);
  }
  printf("\n");
}

int main() {
  solve();
  return 0;
}

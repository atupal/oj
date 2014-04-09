#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
//这是用来找规律的
int n;
int ans[1001];
int max[1001];
long long mm=1L;
int now;
long long s;
int DEBUG=0;

void mul(int ind, int last, int m) {
  if (m < 2*last+3) {
    ans[ind] = m;
    if (DEBUG)for (int i = 0; i <= ind; ++ i) {
      printf("%d ", ans[i]);
    }
    if (DEBUG) printf(":%lld\n", s*m);
    if (s*m > mm) {
      mm=s * m;
      ans[ind+1]=0;
      memcpy(max,ans,sizeof(max));
    }
  }
  else for (int i = last + 1; i <= (m-1)/2; ++ i) {
    ans[ind] = i;
    s *= (long long)i;
    mul(ind+1, i, m-i);
    s /= (long long)i;
  }
}

int main() {
  scanf("%d", &n);
  printf("%d:", n);
  for (int i = 2; i <= (n-1)/2; ++ i) {
    ans[0]=i;
    s=(long long)i;
    mul(1, i, n-i);
  }

  for(int i =0; max[i]; ++ i) 
    printf("%d ", max[i]);
  printf("\n");

  return 0;
}
*/

int n;
int main(){
  scanf("%d", &n);
  //printf("%d:", n);
  int i, s;
  for (i = 3; i < 1001; ++ i)
    if ( (s = (2+i) *(i-1) /2) > n  ) break;
  s -= i; --i;
  int mid = i - (n - s);
  if (mid > 0) {
    for (int x = 2; x <= mid; ++ x) printf("%d ", x);
    for (int x = mid+1; x <= i; ++ x) printf("%d ", x+1);
  } else {
    mid = i + 1 - (n - s - (i - 1));
    for (int x = 3; x <= mid; ++ x) printf("%d ", x);
    for (int x = mid+1; x <= i+1; ++ x) printf("%d ", x+1);
  }
  printf("\n");
}

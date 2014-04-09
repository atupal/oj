
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 101;
int A[maxn];
int n;
int ans;
int min;

void swap(int i, int j) {
    int t = A[i];
    A[i] = A[j];
    A[j] = t;
}

void dfs(int cur, int next_swap) {
    if (A[next_swap] > A[next_swap + 1]) swap(next_swap, next_swap + 1);
    else return;
    int flag = 0;
    for (int i = 1; i < n; ++ i) {
        if (A[i] >= A[i - 1]) continue;
        flag = 1;
        break;
    }
    if (flag)for (int i = 0; i < n - 1; ++ i) {
        dfs(cur + 1, i);
    }
    swap(next_swap, next_swap + 1);
    if (!flag) {
        if (cur < min) {
            ans = 1;
            min = cur;
        }
        else if (cur == min) {
            ++ ans;
        }
    }
}

int main() {
    int cnt = 0;
    while (1) {
        scanf("%d", &n);
        if (!n) return 0;
        for (int i = 0; i < n; ++ i) scanf("%d", &A[i]);

        min = n * n + 1;
        ans = 0;
        for (int i = 0; i < n - 1; ++ i) {
            dfs(1, i);
        }
        printf("There are %d swap maps for input data set %d.\n",ans,++cnt);
    }
    return 0;
}

/*
#include <stdio.h>
int n=0,a[10]={0},mps,cas=0;
bool Isorder()
{
     for(int i=0;i<n-1;i++)
        if(a[i]>a[i+1]) return false;
     return true;
}
void Backtrave()
{
     int t;
     if(Isorder())
        mps++;
     else for(int i=0;i<n-1;i++)
     if(a[i]>a[i+1])
     {
        t=a[i]; a[i]=a[i+1]; a[i+1]=t;
        Backtrave();
        t=a[i]; a[i]=a[i+1]; a[i+1]=t;
     }
}
int main()
{
    while(scanf("%d",&n)==1)
    {
       if(!n) break;
       for(int i=0;i<n;i++)
          scanf("%d",&a[i]);
       mps=0;
       if(!Isorder())
          Backtrave();
       printf("There are %d swap maps for input data set %d.\n",mps,++cas);
    }
    return 0;
}
*/

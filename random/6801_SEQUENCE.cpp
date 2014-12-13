/*
https://icpcarchive.ecs.baylor.edu/external/68/6801.pdf
 */
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long a[1002][1002],T,n,m,i,j,k;
int main() {
    cin >> T;
    int cas=0;
    while (T--)
    {
     int s=0;
     cas++;
     cin >> m >> n;
     for (i=1;i<=m;i++)
     {
         cin >> k;
         if (k==1) s++;
     }
     memset(a,0,sizeof(a));
     a[0][s]=1;
    // printf("%d",m);
     for (i=1;i<=n;i++)
        for (j=0;j<=m;j++)
        {

            a[i][j]=(a[i-1][j-1]*(m-j+1)+a[i-1][j+1]*(j+1))%1000000007;
            if (j==0) a[i][j]=a[i-1][j+1];
            if (j==m) a[i][j]=a[i-1][j-1];
        }
     printf("Case #%d: %lld\n",cas,a[n][0]);
    }
    return 0;
}


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
int T,i;
unsigned long long f[14][14][14][14][5];
int a[5],n;
int h[14][14][14][14][5];

int cha(char c)
{
    if(c=='A') return 1;
    if(c>='2'&&c<='9') return c-'0';
    if(c=='T') return 10;
    if(c=='J') return 11;
    if(c=='Q') return 12;
    return 13;
}


void init()
{
    scanf("%d",&n);
    int i,p[14]={0};
    char s[5];
    for(i=1;i<=n;i++)
     scanf("%s",s),p[cha(s[0])]++;
    memset(a,0,sizeof(a));
    for (i=1;i<=13;i++)
     a[p[i]]++;
}

unsigned long long DFS(int a,int b,int c,int d,int flag)
{
    if(!a&&!b&&!c&&!d) return 1;
    if(h[a][b][c][d][flag]) return f[a][b][c][d][flag];
    h[a][b][c][d][flag]=1;
    unsigned long long ans=0;
    if(a)
    {
        if(flag!=1) ans+=a*DFS(a-1,b,c,d,0);
        else if(a>1) ans+=(a-1)*DFS(a-1,b,c,d,0);
    }
    if(b)
    {
        if(flag!=2) ans+=2*b*DFS(a+1,b-1,c,d,1);
        else if(b>1) ans+=2*(b-1)*DFS(a+1,b-1,c,d,1);
    }
    if(c)
    {
        if(flag!=3) ans+=3*c*DFS(a,b+1,c-1,d,2);
        else if(c>1) ans+=3*(c-1)*DFS(a,b+1,c-1,d,2);
    }
    if(d)
    {
        if(flag!=4) ans+=4*d*DFS(a,b,c+1,d-1,3);
        else if(d>1) ans+=4*(d-1)*DFS(a,b,c+1,d-1,3);
    }
    return f[a][b][c][d][flag]=ans;
}
int main()
{
    memset(h,0,sizeof(h));
    int num=0;
    scanf("%d",&T);
    while (T--)
    {
        init();
        printf("Case #%d: ",++num);
        cout<<DFS(a[1],a[2],a[3],a[4],0)<<endl;
    }
}

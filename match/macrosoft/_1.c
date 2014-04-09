#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int T;
int N;
int M;
int getword(char *f);
char fine[130][25];
char change[130][25];
char first[200][100];
char next[200][100];
int vis[1000];
int num;
int main()
{
    int i,j,k;
    int p,q,z;
    int m;
    scanf("%d",&T);
    for(i=1;i<=T;++i)
    {
        scanf("%d %d",&N,&M);
        for(j=1;j<=M;++j)
        {
            scanf("%s %s",fine[j],change[j]);
        }
        k=0;
        while(getword(first[k])!=0)
        {
            k++;
        }
        for(p=1;p<=N-1;++p)
        {
            num=0;
            for(q=1;q<=M;++q)
            {
                for(z=0;z<=k;++z)
                {
                    if(strcmp(first[z],fine[q])==0)
                    {
                        strcpy(next[z],change[q]);
                        vis[num++]=z;
                    }
                }
            }
            for(m=0;m<num;++m)
            {

                strcpy(first[vis[m]],next[vis[m]]);
            }
        }
        printf("Case #%d:",i);
        for(q=0;q<=k;++q)
        {
            printf(" %s",first[q]);
        }
        printf("\n");
    }
    return 0;
}

int getword(char *f)
{
    int ii=0;
    int c;
    while((c=getchar()) == ' ' || c == EOF);
    f[ii++]=c;
    while((c=getchar())!=32&&c!='\n')
    {
        f[ii++]=c;
    }
    f[ii]='\0';
    if(c=='\n')
    {
        return 0;
    }
    else
        return 1;
}


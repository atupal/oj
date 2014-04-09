
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)

const int maxn = 201;

int n,k;
//int v[maxn][maxn][maxn];
int V[maxn];
int ans[maxn];
int max[maxn];
int s[maxn];

void dfs(int cur, int value) {
    if (cur == k) return;
    int *tmp = (int *) malloc (sizeof(int) * maxn);
    memcpy(tmp, V, sizeof(V));
    for (int i = 0; i <= n * value; ++ i) if(V[i]) {
        for (int j = 1; j <= n - V[i]; ++ j) {
            V[j * value + i] = (j + V[i] < V[j * value + i] || V[j * value + i] == 0) ? j + V[i] : V[j * value + i];
        }
    }
    for (int i = 1; i <= n; ++ i) V[i * value] = i;
    /*
    if (cur)for (int i = value + 1; i <= n * value; ++ i) 
        for (int x = 1; x < n; ++ x) 
            for (int y = n - x; y > 0; -- y)
                for (int j = 0; j < cur; ++ j)
                    if (i - value * x > 0 && v[j][i - value * x][y]) v[cur][i][y + x] = 1;
    for (int i = 1; i <= n; ++ i) v[cur][i * value][i] = 1;
    */
    int x = 1; 
    for (x = 1; x <= n * value + 1 && V[x] != 0; ++ x); --x;
    /*
    while (x <= n * value) {
        int flag = 0;
        for (int i = 0; i <= cur; ++ i) 
            for (int j = 1; j <= n; ++ j)
                if (v[i][x][j]) {flag = 1;goto here;}
here:
        if (flag) x++;
        else {break;}
    }
    x --;
    if (!cur) x = n;
    */
    s[cur] = value;
    if (x > ans[cur]) {
        ans[cur] = x;
        if (cur == k - 1)
        memcpy(max, s, sizeof(s));
    }
    for (int i = value + 1; i <= ans[cur] + 1; ++ i) dfs(cur + 1, i);
    //memset(v[cur], 0, sizeof(v[cur]));
    memcpy(V, tmp, sizeof(V));
    free(tmp);
}

int main () { 
    while (scanf("%d %d", &n, &k)) {
        if (!(n + k)) return 0;
        //memset(v, 0, sizeof(v));
        memset(V, 0, sizeof(V));
        memset(ans, 0, sizeof(ans));
        dfs(0, 1);
        for (int i = 0; i < k; ++ i) printf("%3d", max[i]);
        printf(" ->%3d\n", ans[k- 1]);
    }
}
/*
#include<cstring> 
#include<cstdio>
#include<cstdlib>
#include<iostream>
#define MAXN 200
using namespace std;
int h, k;
int ans[MAXN], maxStampVal, stampVal[MAXN], maxVal[MAXN];
bool occur[MAXN];



// 计算给定面额和数量能够达到的最大连续面值
// cur当前用了几张票， n当前面额数， sum面额之和
void dfs(int cur, int n, int sum){
    if(cur >= h){ 
        occur[sum] = true;    
        return;
    }
  occur[sum] = true;
    for(int i=0; i<=n; ++i){
        dfs(cur+1, n, sum+stampVal[i]);
    }
}

void search(int cur){
    if(cur >= k){
        if(maxVal[cur-1] > maxStampVal){
            maxStampVal = maxVal[cur-1];
            memcpy(ans, stampVal, sizeof(stampVal));
        }
        return ;
    }
    for(int i=stampVal[cur-1]+1; i<=maxVal[cur-1]+1; ++i){

        memset(occur, 0, sizeof(occur));
        stampVal[cur] = i;
        dfs(0, cur, 0);
        int num=0, j=1;
   
        while(occur[j++]) ++num;
        maxVal[cur] = num;

        search(cur+1);
    }
}

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    // h数量， k面额数
    while(scanf("%d %d", &h, &k), h+k){
        stampVal[0] = 1;
        maxVal[0] = h;
        maxStampVal = -2147483645;
        search(1);

        for(int i=0; i<k; ++i)
            printf("%3d", ans[i]);
        printf(" ->%3d\n", maxStampVal);
    }
    return 0;
}
*/

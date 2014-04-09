
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define rep(i, n) for (i = 0; i < n; ++ i)
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

const int maxn = 5;

int A[10];
int getans;
int v[10];
int ans;

void dfs(int why, int cur) {
    if (getans) return;
    if (cur == maxn) {
        //printf("(%d %d) ", ans, why);
        if (why == 23) {
            printf("Possible\n");
            getans = 1;
        }
        return;
    }
    //int Min = why;
    //int Max = why;
    //for (int i = 0; i < maxn; ++ i) if(!v[i]) {
    //    Min = min(min(Min + A[i], Min - A[i]), Min * A[i]);
    //    Max = max(max(Max + A[i], Max - A[i]), Max * A[i]);
    //}
    for (int i = 0; i < maxn; ++ i) if(!v[i]){
        v[i] = 1;
        //ans *= A[i];
        dfs(why * A[i], cur + 1);
        //ans /= A[i];
        //ans += A[i];
        dfs(why + A[i], cur + 1);
        //ans -= A[i];
        //ans -= A[i];
        dfs(why - A[i], cur + 1);
        //ans += A[i];
        v[i] = 0;
    }
}

int main() {
    while (scanf("%d %d %d %d %d", &A[0], &A[1], &A[2], &A[3], &A[4]) == 5) {
        if (!(A[0] + A[1] + A[2] + A[3] + A[4])) return 0;
        getans = 0;
        memset(v, 0, sizeof(v));
        for (int i = 0; i < maxn; ++ i) {
            v[i] = 1;
            if(!getans){ans=A[i];dfs(A[i], 1);}
            v[i] = 0;
        }
        if (!getans)
            printf("Impossible\n");
    }
    return 0;
}


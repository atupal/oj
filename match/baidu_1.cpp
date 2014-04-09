
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n,k;
int A[100010];

int sum;

int ju(int x) {
    int tmp,i, j;
    i = 0;
    j = 0;
    int t = -1;
    while (i < n) {
        tmp = 0;
        while (tmp + A[i]<= x) {
            tmp += A[i];
            ++ i;
        }
        if (t == i) {
            return 0;
        }
        ++ j;
        t = i;
    } 
    if (j <= k) return 1;
    return 0;
}

void solve(){
    int left = sum / k;
    int right = sum;
    for (int i = left; i <= right; ++ i) if (ju(i)){
        printf("%d\n", i);
        return ;
    }
}

int main() {
    while (scanf("%d %d", &n, &k) != EOF) {
        if (n +k == 0)break;
        sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &A[i]);
            sum += A[i];
        }
        solve();
    }
}


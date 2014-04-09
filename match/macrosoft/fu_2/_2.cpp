
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 2010;

int n, n1, n2;
int Q1[maxn];
int C1[maxn];
int Q2[maxn];
int C2[maxn];

int main() {
    int T;
    scanf("%d", &T);
    for (int c = 1; c <= T; ++ c) {
        scanf("%d %d %d", &n, &n1, &n2);
        for (int i = 0; i < n; ++ i) {
            scanf("%d %d %d %d", &Q1[i], &C1[i], &Q2[i], &C2[i]);
        }
        
    }

    return 0;
}


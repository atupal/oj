#include <stdio.h>
#include <string.h>
#include <stdlib.h>


long long get(int x) {
    if (x<=0) return 0L;
    long long n = (long long)x;
    n = (n * (n+1) / 2L);
    return n*n;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++ i) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("Case #%d: %lld\n",i, get(b) - get(a-1));
    }
    return 0;
}

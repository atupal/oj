#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int t;
    scanf("%d", &t);
    int a,b, tmp;
    int n,m;
    while (t--) {
        a = 0, b = 0;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n-1; ++ i) {
            scanf("%d", &tmp);
            a+=tmp;
        }

        for (int i = 0; i < m; ++ i) {
            scanf("%d", &tmp);
            b+=tmp;
        }

        printf("%d %d\n", b/m+1, (a+n-2)/(n-1)-1);
    }

    return 0;
}

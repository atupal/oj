#include <stdio.h>
#include <stdlib.h>

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <=t ; ++ i) {
        double  n;
        scanf("%lf", &n);
        printf("Case #%d: %.0lf\n", i, 8*n*n-7*n+1);
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    int t;
    int n;
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n);
        int cnt = 0;
        for (int i = 2; i < (int)sqrt(n) + 1; ++ i) {
            if (n % i == 0 && n / i % i == 0 && i * i < n) {
                printf("No\n");
                goto here;
            }
            else if (n % i == 0) 
                cnt += 1;
            if (cnt > 1) {
                printf("No\n");
                goto here;
            }
        }
        if (cnt == 1)
            printf("Yes\n");
        else 
            printf("No\n");
here:;
    }

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp( const void *_p, const void *_q)
{
    char *p, *q;
    p = (char *)_p;
    q = (char *)_q;
    return *p - *q;
}


void next(char code[], int n) {
    if (n == 1) {printf("No Successor\n");return;}
    char tmp[n + 1];
    strcpy(tmp, code);
    int flag = n - 2;
    while (tmp[flag] >= tmp[flag + 1]) {
        if (flag) -- flag;
        else {
            printf("No Successor\n");
            return;
        }
    }
    char min;
    for (int i = n - 1; i > flag; -- i) {
        if (tmp[i] > tmp[flag]) {
            min = tmp[i];
            tmp[i] = tmp[flag];
            tmp[flag] = min;
            break;
        }
    }
    qsort(tmp + flag + 1, n - 1 - flag, sizeof(char), cmp);
    //strcpy(code, tmp);
    //for (int i = flag + 1; i < n; ++ i) {
    //    tmp[i] = code[n - (i - flag)];
    //}
    printf("%s\n", tmp);
}


int main() {
    freopen("input", "r", stdin);
    freopen("output.a","w", stdout);
    char tn[101];
    while (1) {
        scanf("%s", tn);
        if (strcmp(tn, "#") == 0) return 0;
        int n = strlen(tn);
        next(tn, n);
    }

    return 0;
}


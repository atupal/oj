
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 500010;

int n;
char **A;

int min(int a, int b) {
    return a < b ?  a : b;
}

char *get(char *a, char *b) {
    int la = strlen(a);
    int lb = strlen(b);
    int l = min(la, lb);
    int x = 0;
    int i = la - 1;

    while (a[x] == b[x] && x < l) ++ x;
    while (a[i] == '1' && i > 0) -- i;

    if(i > x) {
        char *r = (char *) malloc (i + 2);
        memcpy(r, a, i + 2);
        r[i] = '1';
        r[i + 1] = 0;
        return r;
    }
    else {
        if (x == l) {
            char *r = (char *)malloc (l + 3);
            memcpy(r, a, l);
            r[l] = '0';
            r[l + 1] = '1';
            r[l + 2] = 0;
            return r;
        }
        if (x == l - 1) {
            char *r = (char *) malloc (la + 2);
            memcpy(r, a, la);
            r[la] = '1';
            r[la + 1] = 0;
            return r;
        }
        if (x == 0) {
            char *r = (char*) malloc (la + 2);
            memcpy(r, a, la);
            r[la]  = '1';
            r[la +  1] = 0;
            return r;
        }
        char *r = (char *) malloc (x + 2);
        memcpy(r, a, x);

        r[x] = '1';
        r[x + 1] = 0;
        return r;
    }

    return NULL;
}

int main() {
    printf("%s", "001", "01");
    int T;
    scanf("%d", &T);
    A = (char**) malloc (sizeof(char*) * maxn);
    for (int c = 1; c <= T; ++ c) {
        int cnt_1 = 1;
        int cnt = 2;
        A[0] = (char*)malloc (2);
        A[0][0] = '0';
        A[0][1] = 0;
        A[maxn - 1] = (char*)malloc (2);
        A[maxn - 1][0] = '1';
        A[maxn - 1][1] = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            int t;
            scanf("%d", &t);
            int l = t;
            int r = t;
            while (not A[l]) -- l;
            while (not A[r]) ++ r;
            A[t] = get(A[l], A[r]);
            printf("%s\n", A[t]);
            cnt += strlen(A[t]);
            int ind = 0;
            for (; A[t][ind] ;++ind) {
                if (A[t][ind] == '1')
                    cnt_1 +=1;
            }
        }
        for (int i = 0; i < maxn; ++ i) {
            free(A[i]);
            A[i] = NULL;
        }
        printf("Case #%d: %d %d\n", c, cnt, cnt_1);
    }

    return 0;
}


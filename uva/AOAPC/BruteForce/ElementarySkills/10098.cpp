
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    return *((char *)a) - *((char *)b);
}
void swap(char &a, char &b) {
    char t = a;
    a = b;
    b = t;
}

char B[51];
char v[51];
void arr(char *A, int n, int cur) {
    if (cur == n) {
        B[n] = '\0';
        printf("%s\n", B);
    }
    for (int i = 0; i < n; ++ i) {
        if (i < n - 1 && A[i] == A[i + 1] && !v[i + 1]) continue;
        if (v[i]) continue;
        B[cur] = A[i];
        v[i] = 1;
        arr(A, n, cur + 1);
        v[i] = 0;
    }
}

int main () {
    memset(v, 0, sizeof(v));
    int tn;
    scanf("%d", &tn);
    while (tn --) {
        char A[51];
        scanf("%s", A);
        qsort(A, strlen(A), sizeof(char), cmp);
        arr(A, strlen(A), 0);
        printf("\n");
    }
    return 0;
}


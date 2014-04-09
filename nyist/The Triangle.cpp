#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int n;
    scanf("%d", &n);
    int A[n][n];
    memset(A, 0, sizeof(A));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i + 1; ++ j) {
            scanf("%d", &A[i][j]);
        }
    }

    int ans[n][n];
    for (int i = 0; i < n; ++ i) {
        ans[n - 1][i] = A[n - 1][i];
    }
    for (int i = n - 2; i >= 0; -- i) {
        for (int j = i; j >= 0; -- j) {
            ans[i][j] = max(ans[i + 1][j], ans[i + 1][j + 1]) + A[i][j];
        }
    }

    printf("%d\n", ans[0][0]);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rep(i, n) for(int i = 0; i < n; ++ i)

int B[101][20];
int A[101][20];
int n,p;
int flag;

void con(int N, int m, int cur, int *C) {
    if(N - cur == m || !m) {
        for (int i = cur; i < N; ++ i) C[i] = m ? 1 : 0;
        rep(i, n) rep(j, p) B[i][j] = A[i][j];
        rep(i, n) rep(j, p) B[i][j] = B[i][j] & C[j];
        rep(i, n) for (int j = i + 1; j < n; ++ j) 
            if (memcmp(B[i], B[j], sizeof(int) * p) == 0) return;
        flag = 1;
        return;
    }
    C[cur] = 1;
    con(N, m - 1, cur + 1, C);
    C[cur] = 0;
    con(N, m, cur + 1, C);
}

int get(int i) {
    flag = 0;
    int C[p + 1];
    memset(C, 0, sizeof(C));
    con(p, i, 0, C);

    return flag;
}

int main() {
    int tn;
    scanf("%d", &tn);
    while (tn --) {
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        scanf("%d %d", &p, &n);
        rep(i, n) rep(j, p) scanf("%d", &A[i][j]);
        for (int i = 1; i <= p; ++ i) if (get(i)) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}

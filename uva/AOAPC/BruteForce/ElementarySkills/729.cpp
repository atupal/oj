
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void con(int N, int m, int cur, char *C) {
    if(N - cur == m || !m) {
        for (int i = cur; i < N; ++ i) C[i] = m ? '1' : '0';
        C[N] = 0;
        printf("%s\n", C);
        return;
    }
    C[cur] = '0';
    con(N, m, cur + 1, C);
    C[cur] = '1';
    con(N, m - 1, cur + 1, C);
}

int main() {
    int n, c;
    int tn;
    scanf("%d", &tn);
    char B[51];
    while (tn --) {
        scanf("%d %d", &n, &c);
        con(n, c, 0, B);
        if(tn) printf("\n");
    }

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N, M, K;

int get(int n) {
    int A[M];
    for (int i = 0; i < M; ++ i)
        A[i] = n % K;
    for (int i = 0; i < M; ++ i) {
        while (A[i] / K > 0)
            A[i] %= K;

        if (A[i] && i + 1 < M)
            A[i + 1] *= A[i];

        if (i == M - 1 && A[i] % K == 0)
            return 1;
    }

    return 0;
}

int main() {
    scanf("%d %d %d", &N, &M, &K);
    int ans = 0;
    for (int i = 0; i < N; ++ i) {
        int T; 
        scanf("%d", &T);
        if (get(T))
            ++ ans;
    }
    printf("%d\n", ans);

    return 0;
}


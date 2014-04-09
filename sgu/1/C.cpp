
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int A[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31};

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    if (M > 12 || A[M - 1] < N) {
        printf("Impossible\n");
        return 0;
    }
    for (int i = 0; i < M - 1; ++ i) 
        N += A[i];
    int t = (7 * 7 * 7 *7  + 7 + N - 294) % 7;
    printf("%d\n", t == 0 ? 7 : t);

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int na;
int nb;

void solve(int n, int a, int b) {
    if (n > 0) {
        if (a >= b) {
            ++ na;
            solve(n - 1, a - 1, b);
        }
        else {
            ++ nb;
            solve(n - 1, a, b - 1);
        }
    }
}

int main() {
    int n, a,b;
    int T;
    scanf("%d", &T);
    for (int c = 1; c <= T; ++ c) {
        scanf("%d %d %d", &n, &a, &b);
        na = nb = 0;
        solve(n, a, b);
        printf("%s\n", na > nb ? "1" : na == nb ? "0": "-1");
    }

    return 0;
}


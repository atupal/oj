
#include<stdio.h>
#include <stdlib.h>

int v[10];
int A[10] = {5, 8, 9 ,2};
int Bs[10];
char Bp[10];
int first;


void dfs(int cur, int sum) {
    if (cur == 3) {
        if (sum == 56 || sum == 24) {
            printf("%d %d %d %d ",first, Bs[0], Bs[1], Bs[2]);
            printf("%c %c %c\n", Bp[0], Bp[1], Bp[2]);
        }
    }
    else {
        for (int i = 0; i < 4; ++ i) if (!v[i]){
            v[i] = 1;
            Bs[cur] = A[i];
            Bp[cur] = '+';
            dfs(cur + 1, sum + A[i]);
            Bp[cur] = '/';
            if(!(sum % A[i]))dfs(cur + 1, sum / A[i]);
            Bp[cur] = '*';
            dfs(cur + 1, sum * A[i]);
            Bp[cur] = '-';
            dfs(cur + 1, sum - A[i]);
            v[i] = 0;
        }
    }
}

int main() {
    for (int i = 0; i < 4; ++ i) 
    {
        first = A[i];
        v[i] = 1;
        dfs(0, A[i]);
        v[i] = 0;
    }
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 50002;
char s[maxn];
char p[maxn];

void solve() {
}

int main() {
    int T;
    scanf("%d", &T);
    for(int c = 1;  c <= T; ++ c){
        scanf("%s", s);
        scanf("%s", p);
        int min = maxn;
        for (int i = 0; i <= strlen(s) - strlen(p); ++ i) {
            int cnt = 0;
            for (int j = 0; j < strlen(p); ++ j) {
                if (s[i + j] != p[j]) {
                    ++ cnt;
                }
            }
            min = min < cnt ? min : cnt;
        }
        printf("Case #%d: %d\n",c,  min);
    }

    return 0;
}


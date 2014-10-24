
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

inline
char get() {
    char a;
    a = getchar();
    if (a != EOF) {
        return a;
    }
    return 0;
    exit(0);
}

char s[9000];

void solve() {
    int cnt = 0;
    while (s[cnt++] = get());
    for (int i = 0; i < cnt; ++ i) {
        if (s[i] == 'A') {
            if (i+4<cnt and s[i+1]=='p' and s[i+2]=='p' and s[i+3]=='l' and s[i+4]=='e') {
                printf("MAI MAI MAI!\n");
            }
        } else if (s[i] == 'i') {
            if (i+1<cnt and s[i+1]=='P') {
                if (i+5 < cnt and s[i+2] == 'h' and s[i+3]=='o' and s[i+4]=='n' and s[i+5]=='e') {
                    printf("MAI MAI MAI!\n");
                }
                else if (i+3<cnt and s[i+2]=='o' and s[i+3]=='d') {
                    printf("MAI MAI MAI!\n");
                }
                else if (i+3<cnt and s[i+2]=='a' and s[i+3]=='d') {
                    printf("MAI MAI MAI!\n");
                }
            }
        } else if (s[i]=='S') {
            if (i+3 <cnt and s[i+1]=='o' and s[i+2]=='n' and s[i+3]=='y') {
                printf("SONY DAFA IS GOOD!\n");
            }
        }
    }
}

int main() {
    solve();
    return 0;
}

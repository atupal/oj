
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rep(i) for (i = 1; i <= 3; ++ i)
#define rem(i) for (i = 0; i <= 1; ++ i)

char s[51][101];
int n;
int ans[6];
int v[6];


int judge(int *five, int day) {

    int i;
    int flag = 0;
    for (i = 0; i < 5; ++ i) if (v[i] && five[i] != ans[i]) flag = 1;
    if (v[i] && ans[5] != day) flag = 1;
    if (!flag) return 0;


    for (int i = 0; i < n; ++ i) {
        char who = five[s[i][0] - 'A'];
        char isnot;
        if (strstr(s[i], "not")) isnot = 4;
        else isnot = 0;
        if (strstr(s[i], "divine")) isnot += 1;
        else if (strstr(s[i], "human")) isnot += 2;
        else if (strstr(s[i], "evil")) isnot += 3;
        else if (strstr(s[i], "lying")) isnot += 4;
        if (s[i][3] == 'I' && s[i][4] == ' ') {
            if (isnot == 1) if (who == 1 || who == 3 || (who == 2 && day == 0));
            else return 0;
            if (isnot == 2) if ((who == 2 && day == 1) || who == 3);
            else return 0;
            if (isnot == 3) if (who == 2 && day == 0);
            else return 0;
            if (isnot == 4) return 0;
            else;
            if (isnot == 5) if ((who == 2 && day == 1));
            else return 0;
            if (isnot == 6) if (who == 1 || (who == 2 && day == 0));
            else return 0;
            if (isnot == 7) if (who == 1 || (who == 2 && day == 1));
            else return 0;
        }
        int X = s[i][3] - 'A';
        if (X < 5 && X >= 0) {
            if (isnot == 1) if ((who == 1 && five[X] == 1) || (who == 2 && day == 1 && five[X] == 1) || (who == 2 && day == 0 && five[X] != 1) || (who == 3 && five[X] != 1));
            else return 0;
            if (isnot == 2) if ((who == 1 && five[X] == 2) || (who == 2 && day == 1 && five[X] == 2) || (who == 2 && day == 0 && five[X] != 2) || (who == 3 && five[X] != 2));
            else return 0;
            if (isnot == 3) if ((who == 1 && five[X] == 3) || (who == 2 && day == 1 && five[X] == 3) || (who == 2 && day == 0 && five[X] != 3) || (who == 3 && five[X] != 3));
            else return 0;
            if (isnot == 4) if ((who == 1 && (five[X] == 3 || (five[X] == 2 && day == 0))) || (who == 2 && day == 1 && (five[X] == 3 || (five[X] == 2 && day == 0))) || (who == 2 && day == 0 && (five[X] == 1 || (five[X] == 2 && day == 1))) || (who == 3 && (five[X] == 1 || (five[X] == 2 && day == 0))));
            else return 0;
            if (isnot == 5) if ((who == 1 && five[X] != 1) || (who == 2 && day == 1 && five[X] != 1) || (who == 2 && day == 0 && five[X] == 1) || (who == 3 && five[X] == 1));
            else return 0;
            if (isnot == 6) if ((who == 1 && five[X] != 2) || (who == 2 && day == 1 && five[X] != 2) || (who == 2 && day == 0 && five[X] == 2) || (who == 3 && five[X] == 2));
            else return 0;
            if (isnot == 7) if ((who == 1 && five[X] != 3) || (who == 2 && day == 1 && five[X] != 3) || (who == 2 && day == 0 && five[X] == 3) || (who == 3 && five[X] == 3));
            else return 0;
            if (isnot == 8) if ((who == 1 && (five[X] == 1 || (five[X] == 2 && day == 1))) || (who == 2 && day == 1 && (five[X] == 1 || (five[X] == 2 && day == 1))) || (who == 2 && day == 0 && (five[X] == 3 || (five[X] == 2 && day == 0))) || (who == 3 && (five[X] == 3 || (five[X] == 2 && day == 0))));
            else return 0;
        }
        if (s[i][3] == 'I' && s[i][4] == 't') {
            char isday;
            if (strstr(s[i], "day")) isday = 1;
            else isday = 0;
            if (who == 1) if (day == isday);
            else continue;
            if (who == 2 && day == 1) if (day == isday);
            else continue;
            if (who == 2 && day == 0) if (day != isday);
            else continue;
            if (who == 3) if (day != isday) ;
            else continue;
        }
    }

    memcpy(ans, five, sizeof(int) * 5);
    ans[5] = day;
    return 1;
}

int main() {
    char out[3][51] = {"divine.", "human.", "evil."};
    int ccc = 0;
    while ((scanf("%d", &n), n)) {
        ++ ccc;
        getchar();
        for (int i = 0; i < n; ++ i) {
            gets(s[i]);
        }
        memset(ans, -1, sizeof(ans));
        int cnt = 0;

        memset(v, 0, sizeof(v));
        for(int i = 0; i < n; ++ i){ if (strstr(s[i], "A")) v[0] = 1;if(strstr(s[i], "B")) v[1] = 1;
        if (strstr(s[i], "C")) v[2] = 1;if (strstr(s[i], "D")) v[3] = 1;if (strstr(s[i], "E")) v[4] = 1;if(strstr(s[i], "It")) v[5]=1;}

        int five[5];int &A=five[0],&B=five[1],&C=five[2],&D=five[3],&E=five[4],day;
        rep(A) rep(B) rep(C) rep(D) rep(E) rem(day) if (judge(five, day)) ++ cnt;
        printf("Conversation #%d\n", ccc);
        if (!cnt) printf("This is impossible.\n");
        else if (cnt > 1) printf("No facts are deducible.\n");
        else {
            for (int i = 0; i < 5; ++ i) if (v[i]) 
                printf("%c is %s\n", i + 'A', out[ans[i] - 1]);
            for (int i = 0; i < 5; ++ i) if (v[i] && ans[i] == 2) {
                printf("It is %s", ans[5] ? "day." : "night.");
            }
        }
        printf("\n");
    }

    return 0;
}


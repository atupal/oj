/*
    http://blog.csdn.net/wings_of_liberty/article/details/7376756
*/

/*
   zoj 70 ms可过 poj tle .....
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>

//#define DEBUG

using namespace std;

const int maxn = 111;

int t;
char *s;

map<string, int> ha;

struct var {
  double val;
  char name[22];
};
var ra[2];
var rb[2];
var zero = {0., "zero"};

struct cmd {
  int type;
  var ret;
  var left;
  var right;
};

double vars[maxn];
int varcnt;
cmd cmds[2][maxn];
int cmdcnt[2];

double dp[maxn][maxn][maxn];
double p1[maxn][maxn];
double p2[maxn][maxn];
double p[maxn][maxn];

inline
void low(char *s) {
  int l = strlen(s);
  for (int i = 0; i < l; ++ i) {
    if (s[i] <= 'Z' && s[i] >= 'A') 
      s[i] = 'a' + s[i] - 'A';
  }
  for (int i = l-1; i; -- i) {
    if (s[i] == ' '||s[i] == '\n'||s[i] == '\t') {
      s[i] = '\0';
    } else {
      break;
    }
  }
}

void input(int ind) {
  var tmp;
  while (1) {
    //size_t l;
    int i,b;
    //getline(&s, &l, stdin);
    gets(s);
    low(s);
    if (strcmp(s, "end\n") == 0||strcmp("end", s) == 0) break;
    i = 0;
    while (s[i] == ' '||s[i] == '\t'||s[i] == '\n') ++ i;
    if (i == (int)strlen(s)) continue;

    i = 0;

    while (s[i] == ' '||s[i] == '\t') ++ i;
    b = i;
    while ((s[i] <= 'z' && s[i] >= 'a')||(s[i] <= '9' && s[i] >= '0')) ++ i;
    strncpy(tmp.name, s+b, i-b),tmp.name[i-b] = '\0';
    /*
    cmds[ind][cmdcnt[ind]+3] = (struct cmd) {
      .type=1,
      .ret=tmp,
      .left = ra[ind],
      .right = zero
    };
    */
    cmds[ind][cmdcnt[ind]+3] = (struct cmd) { 1, tmp, ra[ind], zero };
    if (not ha.count(tmp.name)) {
      ha[tmp.name] = varcnt;
      ++ varcnt;
    }

    while (s[i] == ' '||s[i] == '\t'||s[i] == ':'||s[i] == '=') ++ i;
    b = i;
    while ((s[i] <= 'z' && s[i] >= 'a')||(s[i] <= '9' && s[i] >= '0')) ++ i;
    strncpy(tmp.name, s+b, i-b),tmp.name[i-b] = '\0';
    if (s[b] <= 'z' && s[b] >= 'a') {
      if (not ha.count(tmp.name)) {
        ha[tmp.name] = varcnt;
        ++ varcnt;
      }
    } else {
      tmp.val = 0.;
      for (int x = b; x < i; ++ x) {
        tmp.val = tmp.val * 10 + (s[x] - '0');
      }
    }
    cmds[ind][cmdcnt[ind]] = (struct cmd) { 1, ra[ind], tmp, zero };


    while (s[i] == ' '||s[i] == '\t') ++ i;
    if (s[i] == '+') {
      cmds[ind][cmdcnt[ind]+2] = (struct cmd) { 1, ra[ind], ra[ind], rb[ind] };
    } else {
      cmds[ind][cmdcnt[ind]+2] = (struct cmd) { 2, ra[ind], ra[ind], rb[ind]  };
    }
    ++ i;

    while(s[i] == ' '||s[i] == '\t') ++ i;
    b = i;
    while ((s[i] <= 'z' && s[i] >= 'a')||(s[i] <= '9' && s[i] >= '0')) ++ i;
    strncpy(tmp.name, s+b, i-b),tmp.name[i-b] = '\0';
    if (s[b] <= 'z' && s[b] >= 'a') {
      if (not ha.count(tmp.name)) {
        ha[tmp.name] = varcnt;
        ++ varcnt;
      }
    } else {
      tmp.val = 0.;
      for (int x = b; x < i; ++ x) {
        tmp.val = tmp.val * 10 + (s[x] - '0');
      }
    }
    cmds[ind][cmdcnt[ind]+1] = (struct cmd) { 1, rb[ind], tmp, zero };
    cmdcnt[ind] += 4;
  }
  cmdcnt[ind] -= 1;
}

void init() {
  ra[0] = (struct var) {0., "_ra1"};
  rb[0] = (struct var) {0., "_rb1"};
  ra[1] = (struct var) {0., "_ra2"};
  rb[1] = (struct var) {0., "_rb2"};
  ha.clear();
  ha[ra[0].name] = 0;
  ha[rb[0].name] = 1;
  ha[ra[1].name] = 2;
  ha[rb[1].name] = 3;
  varcnt = 4;
  cmdcnt[0] = 1;
  cmdcnt[1] = 1;
}

void solve() {
  double k1, k2;
  int r;
  double a, b;

#ifdef DEBUG
  for (int i = 1; i <= cmdcnt[0]; ++ i) {
    printf("cmd0: %s = %s %c %s\n", cmds[0][i].ret.name,
                              cmds[0][i].left.name,
                              cmds[0][i].type == 1 ? '+' : '-',
                              cmds[0][i].right.name);
  }
  printf("***************************\n");
  for (int i = 1; i <= cmdcnt[1]; ++ i) {
    printf("cmd1: %s = %s %c %s\n", cmds[1][i].ret.name,
                              cmds[1][i].left.name,
                              cmds[1][i].type == 1 ? '+' : '-',
                              cmds[1][i].right.name);
  }
  printf("***************************\n");
  for(map<string, int>::const_iterator it = ha.begin() ; it != ha.end(); ++ it) {
    printf("%s: %d\n", it->first.c_str(), it->second);
  }
  printf("***************************\n");
#endif
  p[0][0] = 1.;
  for (int i = 0; i < maxn; ++ i) {
    dp[0][0][i] = 0.;
  }
  for (int x = 1; x <= cmdcnt[0]; ++ x) {
    p[x][0] = p[x-1][0] * .5;
    for (int k = 0; k < varcnt; ++ k) {
      dp[x][0][k] = dp[x-1][0][k];
    }
    r = ha[cmds[0][x].ret.name];
    if (ha.count(cmds[0][x].left.name)) 
      a = dp[x-1][0][ha[cmds[0][x].left.name]];
    else
      a = cmds[0][x].left.val;
    if (ha.count(cmds[0][x].right.name)) 
      b = dp[x-1][0][ha[cmds[0][x].right.name]];
    else
      b = cmds[0][x].right.val;
    if (cmds[0][x].type != 1) 
      b = -b;
    dp[x][0][r] = a + b;
  }
#ifdef DEBUG
  for(map<string, int>::const_iterator it = ha.begin() ; it != ha.end(); ++ it) {
    printf("%s: %lf\n",it->first.c_str(), dp[cmdcnt[0]][0][it->second]);
  }
  printf("***************************\n");
#endif
  for (int x = 1; x <= cmdcnt[1]; ++ x) {
    p[0][x] = p[0][x-1] * .5;
    for (int k = 0; k < varcnt; ++ k) {
      dp[0][x][k] = dp[0][x-1][k];
    }
    r = ha[cmds[1][x].ret.name];
    if (ha.count(cmds[1][x].left.name)) 
      a = dp[0][x-1][ha[cmds[1][x].left.name]];
    else
      a = cmds[1][x].left.val;
    if (ha.count(cmds[1][x].right.name)) 
      b = dp[0][x-1][ha[cmds[1][x].right.name]];
    else
      b = cmds[1][x].right.val;
    if (cmds[1][x].type != 1) 
      b = -b;
    dp[0][x][r] = a + b;
  }
#ifdef DEBUG
  for(map<string, int>::const_iterator it = ha.begin() ; it != ha.end(); ++ it) {
    printf("%s: %lf\n",it->first.c_str(), dp[0][cmdcnt[1]][it->second]);
  }
  printf("***************************\n");
#endif

  for (int i = 1; i <= cmdcnt[0]; ++ i) {
    for (int j = 1; j <= cmdcnt[1]; ++ j) {

      if ( i == cmdcnt[0] && j == cmdcnt[1] ) p1[i][j] = p[ i-1 ][ j ]  ,p2[i][j] = p[ i ][ j-1 ];
      if ( i  < cmdcnt[0] && j == cmdcnt[1] ) p1[i][j] = p[ i-1 ][ j ]  ,p2[i][j] = p[ i ][ j-1 ]/2.;
      if ( i == cmdcnt[0] && j  < cmdcnt[1] ) p1[i][j] = p[ i-1 ][ j ]/2.,p2[i][j] = p[ i ][ j-1 ];
      if ( i  < cmdcnt[0] && j  < cmdcnt[1] ) p1[i][j] = p[ i-1 ][ j ]/2.,p2[i][j] = p[ i ][ j-1 ]/2. ;
      p[i][j] = p1[i][j] + p2[i][j];

      for (int k = 0; k < varcnt; ++ k) {
        if (ha[cmds[0][i].ret.name] == k) {
          if (ha.count(cmds[0][i].left.name)) 
            a = dp[i-1][j][ha[cmds[0][i].left.name]];
          else
            a = cmds[0][i].left.val;
          if (ha.count(cmds[0][i].right.name)) 
            b = dp[i-1][j][ha[cmds[0][i].right.name]];
          else
            b = cmds[0][i].right.val;
          if (cmds[0][i].type != 1) 
            b = -b;
          k1 = a + b;
        } else {
          k1 = dp[i-1][j][k];
        }

        if (ha[cmds[1][j].ret.name] == k) {
          if (ha.count(cmds[1][j].left.name)) 
            a = dp[i][j-1][ha[cmds[1][j].left.name]];
          else
            a = cmds[1][j].left.val;
          if (ha.count(cmds[1][j].right.name)) 
            b = dp[i][j-1][ha[cmds[1][j].right.name]];
          else
            b = cmds[1][j].right.val;
          if (cmds[1][j].type != 1) 
            b = -b;
          k2 = a + b;
        } else {
          k2 = dp[i][j-1][k];
        }

        dp[i][j][k] = (p1[i][j] * k1 + p2[i][j] * k2) / p[i][j];

      }

    }
  }

#ifdef DEBUG
  for(map<string, int>::const_iterator it = ha.begin() ; it != ha.end(); ++ it) {
    printf("%s: %lf\n",it->first.c_str(), dp[cmdcnt[0]][cmdcnt[1]][it->second]);
  }
#endif
  for(map<string, int>::const_iterator it = ha.begin() ; it != ha.end(); ++ it) {
    if (it->second >= 4)
      printf("%.4lf\n", dp[cmdcnt[0]][cmdcnt[1]][it->second]);
  }
}

int main() {
  scanf("%d\n", &t);
  s = (char *) malloc (maxn);
  while (t --) {
    init();
    input(0);
    input(1);
    solve();
    if (t)
      printf("\n");
  }
  return 0;
}

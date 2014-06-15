#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 30;
int n;

static struct {
  int cnt;
  int block[maxn];
} stack[maxn];

static struct {
  int sindex;
  int bindex;
} pos[maxn];

void init() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    stack[i].cnt = 1;
    stack[i].block[0] = i;
    pos[i].sindex = i;
    pos[i].bindex = 0;
  }
}

int same_stack(int type, int a, int b) {
  return pos[a].sindex == pos[b].sindex;
  return 0;
}

/* move block b on the top of stack over stack s */
void move(int b, int s) {
  -- stack[pos[b].sindex].cnt;
  stack[s].block[stack[s].cnt++] = b;
  pos[b].sindex = s;
  pos[b].bindex = stack[s].cnt - 1;
}
/*
move: 2
over: 1
 */
/* pile onto */
void exec0(int a, int b) {
  int t;
  t = stack[pos[b].sindex].cnt;
  for (int x = pos[b].bindex+1; x < t; ++ x) {
    move(stack[pos[b].sindex].block[x], stack[pos[b].sindex].block[x]);
  }
  t = stack[pos[a].sindex].cnt;
  int s = pos[a].sindex;
  for (int x = pos[a].bindex; x < t; ++ x) {
    move(stack[s].block[x], pos[b].sindex);
  }
}
/* pile over */
void exec1(int a, int b) {
  exec0(a, stack[pos[b].sindex].block[stack[pos[b].sindex].cnt-1]);
}
/* move onto */
void exec2(int a, int b) {
  int t;
  t = stack[pos[a].sindex].cnt;
  for (int x = pos[a].bindex+1; x < t; ++ x) {
    move(stack[pos[a].sindex].block[x], stack[pos[a].sindex].block[x]);
  }
  t = stack[pos[b].sindex].cnt;
  for (int x = pos[b].bindex+1; x < t; ++ x) {
    move(stack[pos[b].sindex].block[x], stack[pos[b].sindex].block[x]);
  }
  move(a, pos[b].sindex);
}
/* move over */
void exec3(int a, int b) {
  exec0(a, stack[pos[b].sindex].block[stack[pos[b].sindex].cnt-1]);
}

void (*exec[4]) (int, int) = {exec0, exec1, exec2, exec3};

void out() {
  for (int i = 0; i < n; ++ i) {
    printf("%d:", i);
    for (int x = 0; x < stack[i].cnt; ++ x) {
      printf(" %d", stack[i].block[x]);
    }
    printf("\n");
  }
}

void solve() {
  char s[256];
  int type;
  int a, b;
  while (1) {
    type = 0;
    scanf("%s", s);
    if (strcmp(s, "quit") == 0) {
      return;
    } else if (strcmp(s, "move") == 0) {
      type += 2;
    }
    scanf("%d", &a);
    scanf("%s", s);
    if (strcmp(s, "over") == 0) {
      type += 1;
    }
    scanf("%d", &b);
    //printf("%s %d %s %d\n", type / 2 ? "move " : "pile ", a, type % 2 ? " over " : " onto ",  b);
    if (not same_stack(type, a, b)) {
      exec[type](a, b);
      //out();
      //printf("\n");
    } else {
      //printf("no action\n\n");
    }
  }
}

int main() {
  init();
  solve();
  out();
  return 0;
}

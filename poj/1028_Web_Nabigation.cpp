#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char back[101][71];
int b_v = -1;
char forw[101][71];
int f_v = -1;

void b_push(char *s) {
  strcpy(back[++b_v], s);
}
void f_push(char *s) {
  strcpy(forw[++f_v], s);
}
char* b_pop() {
  if (b_v<0) return "Ignored";
  else return back[b_v--];
}
char* f_pop() {
  if (f_v<0) return "Ignored";
  else return forw[f_v--];
}
void empty(){f_v=-1;}

int main() {
  char now[101];
  strcpy(now, "http://www.acm.org/");
  for(;;) {
    char s[71];
    scanf("%s", s);
    if (strcmp(s, "VISIT") == 0) {
      scanf("%s", s);
      printf("%s\n", s);
      b_push(now);
      strcpy(now, s);
      empty();
    } else if (strcmp(s, "BACK") == 0) {
      char *url=b_pop();
      if (strcmp(url, "Ignored")!=0) {
        f_push(now);
        strcpy(now, url);
      }
      printf("%s\n", url);
    } else if (strcmp(s, "FORWARD") == 0) {
      char *url=f_pop();
      if (strcmp(url, "Ignored")!=0) {
        b_push(now);
        strcpy(now, url);
      }
      printf("%s\n", url);
    } else {
      return 0;
    }
  }
}

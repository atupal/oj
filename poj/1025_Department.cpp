#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <queue>
#include <vector>
#include <functional>


struct List{
  int floor;
  int room;
  int time;
  List *next;
};

struct State{
};

struct Person{
  List *list;
  List *tail;
  State state;
  int init_time;
} person[26];

void input() {
  char code;
  while ((scanf("%c", &code), code) != '.') {
    int ind = code - 'A';
    char str[256];
    scanf("%s", str);
    short h, m, s;
    sscanf(str, "%hi:%hi:%hi", &h, &m, &s);
    person[ind].init_time = h * 3600 + m * 60 + s;
    gets(str);
    while (strlen(str) > 3) {
      int _1, _2;
      sscanf(str, "%d %d", &_1, &_2);
      List tmp = List{_1/100, _1%100, _2, NULL};
      if (not person[ind].list) {
        person[ind].list = &tmp;
        person[ind].tail = &tmp;
      } else {
        person[ind].tail->next = &tmp;
      }
    }
  }
}

void output() {
}

void print_time(int sec) {
  printf("%.2d:%.2d:%.2d ", sec / 3600, sec % 3600 / 60, sec % 60);
}

void solve() {
}

int main(int args, char **argv) {
  input();
  return 0;
}
input();

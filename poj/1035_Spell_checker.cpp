#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;

int DEBUG=0;

typedef struct node {
  bool isword;
  node *next[26];
  node() {
    isword = false;
    memset(next, 0, sizeof(next));
  }
} node;


int cmp(const void *a, const void *b)
{
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
}


void insert(node *root, char *s) {
  int len = strlen(s);
  for (int i = 0; i < len; ++ i) {
    int ind = s[i] - 'a';
    if (! root->next[ind]) {
      root->next[ind] = new node;
    }
    root = root->next[ind];
  }
  root->isword = true;
}

bool find(node *root, char *s) {
  int len = strlen(s);
  for (int i = 0; i < len; ++ i) {
    int ind = s[i] - 'a';
    if (!root->next[ind]) {
      return false;
    }
    root = root->next[ind];
  }

  if (root->isword) {
    return true;
  }

  return false;
}

bool equals(char *s1, char *s2) {
  if (DEBUG) printf("\n# %s-%s:\n", s1, s2);
  int l1 = strlen(s1);
  int l2 = strlen(s2);
  int cnt = 0;
  int i = 0, j = 0;
  if (l1 != l2) {
    while (i < l1 and j < l2) {
      if (s1[i] != s2[j]) {
        cnt ++;
        if (cnt > 1) { if(DEBUG)printf("%c-%c", s1[i], s2[j]);  return false; }
        i += l1 > l2 ? 1 : 0;
        j += l1 < l2 ? 1 : 0;
      } else {
        ++i;
        ++j;
      }
    }

    return true;
  } else {
    while (i < l1) {
      if (s1[i] != s2[i]) {
        cnt += 1;
        if (cnt > 1) { if(DEBUG)printf("%c-%c", s1[i], s2[j]);  return false; }
      }
      ++i;
    }
    return true;
  }
}

int main(int args, char **argv) {
  //DEBUG=1;
  char s[256];
  int n = 0;
  node *root = new node;
  char *ss[10005];
  for (int i = 0; i < 10005; ++ i) 
    ss[i] = (char *) malloc (sizeof(char) * 55);
  while(  (scanf("%s", ss[n++]), strcmp(ss[n-1],"#")) ) {
    insert(root, ss[n-1]);
  }
  n--;
  //qsort(ss, n , sizeof(char*), cmp);
  //for (int i = 0; i< n; ++ i) printf("%s ", ss[i]);
  //printf("\n");
  //return 0;
  while(  (scanf("%s", s), strcmp(s,"#")) ) {
    if (find(root, s)) {
      printf("%s is correct\n", s);
    } else {
      printf("%s:", s);
      for (int i = 0; i< n; ++ i) {
        int dis = strlen(ss[i]) - strlen(s);
        if (dis <= 1 && dis >= -1) {
          if (equals(ss[i], s)) {
            printf(" %s", ss[i]);
          }
        }
      }
      printf("\n");
    }
  }

  return 0;
}

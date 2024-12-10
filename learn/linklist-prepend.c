#include "stdio.h"
#include <stdlib.h>
#include <sys/_types/_null.h>

// cannot use binary search algorithm in linklist

typedef struct node {
  int number;
  struct node *next;
} node;

int main(int argc, char *argv[]) {
  node *list = NULL;

  // prepending
  for (int i = 1; i < argc; i++) {
    node *n = malloc(sizeof(node));
    if (n == NULL) {
      free(list);
      printf("cannot take memory location for temp\n");
      return 1;
    }

    n->number = atoi(argv[i]);
    n->next = list;
    list = n;
  }

  node *ptr = list;
  while (ptr != NULL) {
    printf("%i\n", ptr->number);
    ptr = ptr->next;
  }

  free(ptr);
  free(list);
  return 0;
}

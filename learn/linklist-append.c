#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>

typedef struct node {
  int number;
  struct node *next;
} node;

int main(int argc, char *argv[]) {
  node *list = NULL;

  // appending
  for (int i = 1; i < argc; i++) {
    node *n = malloc(sizeof(node));

    if (n == NULL) {
      free(list);
      printf("cannot take memory location for temp\n");
      return 1;
    }

    n->number = atoi(argv[i]);
    n->next = NULL;

    if (list == NULL) {
      list = n;
    } else if (n->number < list->number) {
      n->next = list;
      list = n;
    } else {
      for (node *ptr = list; ptr != NULL; ptr = ptr->next) {
        if (ptr->next == NULL) {
          ptr->next = n;
          break;
        }
        if (n->number < ptr->next->number) {
          n->next = ptr->next;
          ptr->next = n;
          break;
        }
      }
    }
  }

  node *toPrint = list;
  while (toPrint != NULL) {
    printf("%i\n", toPrint->number);
    toPrint = toPrint->next;
  }

  free(toPrint);
  free(list);
  return 0;
}

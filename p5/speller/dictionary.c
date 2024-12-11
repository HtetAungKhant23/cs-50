// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
unsigned int hash_idx;
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
  // TODO
  hash_idx = hash(word);
  node *current = table[hash_idx];
  while (current != 0) {
    if (strcasecmp(word, current->word) == 0) {
      return true;
    }
    current = current->next;
  }
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
  // TODO: Improve this hash function
  unsigned int total = 0;
  int idx = 0;
  while (word[idx] != '\0') {
    total += tolower(word[idx]);
    idx++;
  }
  return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  FILE *openedDic = fopen(dictionary, "r");
  if (openedDic == NULL) {
    printf("unable to open %s\n", dictionary);
    return false;
  }

  char word[LENGTH + 1];
  while (fscanf(openedDic, "%s", word) != EOF) {
    node *n = malloc(sizeof(node));
    if (n == NULL) {
      return false;
    }

    strcpy(n->word, word);
    hash_idx = hash(word);
    n->next = table[hash_idx];
    table[hash_idx] = n;
    word_count++;
  }

  fclose(openedDic);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
  // TODO
  return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  // TODO
  for (int i = 0; i < N; i++) {
    while (table[i] != NULL) {
      node *temp = table[i];
      table[i] = table[i]->next;
      free(temp);
    }
  }
  return true;
}

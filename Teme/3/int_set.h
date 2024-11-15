#include <stdlib.h>

typedef struct {
  int *data;
  size_t size;
  size_t capacity;
} int_set;

int_set int_set_new(size_t capacity);

void free_set(int_set *set);

void int_set_insert(int_set *set, int value);

bool int_set_contains(int_set *set, int value);

void int_set_remove(int_set *set, int value);

void int_set_print(int_set *set);

#include "insertion_sort.h"
#include <limits.h>
#include <string.h>

typedef int (*Comparator)(const void *, const void *);

void insertion_swap(void *a, void *b, size_t element_size) {
  char temp[element_size];
  memcpy(temp, a, element_size);
  memcpy(a, b, element_size);
  memcpy(b, temp, element_size);
}

void insertionsort(void *array, size_t array_size, size_t element_size,
                   Comparator cmp) {
  char *base = (char *)array;
  for (size_t i = 1; i < array_size; i++) {
    for (size_t j = i; j != SIZE_T_MAX; j--) {
      char *a = base + j * element_size;
      char *b = base + (j - 1) * element_size;
      if (cmp(a, b) < 0) {
        insertion_swap(a, b, element_size);
      } else {
        break;
      }
    }
  }
}

#include "../libraries/insertionsort.h"
#include "../libraries/swap.h"
#include <limits.h>

void insertionsort(void *array, size_t array_size, size_t element_size,
                   Comparator cmp) {
  char *base = (char *)array;
  for (size_t i = 1; i < array_size; i++) {
    for (size_t j = i; j != SIZE_T_MAX; j--) {
      char *a = base + j * element_size;
      char *b = base + (j - 1) * element_size;
      if (cmp(a, b) < 0) {
        swap_elements(a, b, element_size);
      } else {
        break;
      }
    }
  }
}

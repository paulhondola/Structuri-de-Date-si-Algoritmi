#include "../libraries/selectionsort.h"
#include "../libraries/swap.h"

void selectionsort(void *array, size_t array_size, size_t element_size,
                   Comparator cmp) {
  char *base = (char *)array;
  for (size_t i = 0; i < array_size - 1; i++) {
    size_t min_index = i;
    for (size_t j = i + 1; j < array_size; j++) {
      char *a = base + min_index * element_size;
      char *b = base + j * element_size;
      if (cmp(a, b) > 0) {
        min_index = j;
      }
    }
    if (min_index != i) {
      char *a = base + i * element_size;
      char *b = base + min_index * element_size;
      swap_elements(a, b, element_size);
    }
  }
}

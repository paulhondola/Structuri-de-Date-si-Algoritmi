#include "../libraries/bubblesort.h"
#include "../libraries/swap.h"

void bubblesort(void *array, size_t array_size, size_t element_size,
                Comparator cmp) {
  char *base = (char *)array;
  int sorted = 0;
  do {
    sorted = 1;
    for (size_t i = 0; i < array_size - 1; i++) {
      void *current_element = base + i * element_size;
      void *next_element = base + (i + 1) * element_size;
      if (cmp(current_element, next_element) > 0) {
        swap_elements(current_element, next_element, element_size);
        sorted = 0;
      }
    }
  } while (!sorted);
}

#include "bubblesort.h"
#include <string.h>

void swap(void *a, void *b, size_t element_size) {
  char temp[element_size];
  memcpy(temp, a, element_size);
  memcpy(a, b, element_size);
  memcpy(b, temp, element_size);
}

void bubblesort(void *array, int array_size, int element_size, Comparator cmp) {
  char *base = (char *)array;
  int sorted = 0;
  do {
    sorted = 1;
    for (size_t i = 0; i < array_size - 1; i++) {
      void *current_element = base + i * element_size;
      void *next_element = base + (i + 1) * element_size;
      if (cmp(current_element, next_element) > 0) {
        swap(current_element, next_element, element_size);
        sorted = 0;
      }
    }
  } while (!sorted);
}

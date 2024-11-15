#include "quicksort.h"
#include <string.h>

typedef int (*Comparator)(const void *, const void *);

void quick_swap(void *a, void *b, size_t element_size) {
  char temp[element_size];
  memcpy(temp, a, element_size);
  memcpy(a, b, element_size);
  memcpy(b, temp, element_size);
}

int partition(void *arr, int low, int high, size_t element_size,
              Comparator cmp) {
  char *base = (char *)arr;
  void *pivot = base + high * element_size;
  int i = low - 1;

  for (int j = low; j < high; j++) {
    void *current_element = base + j * element_size;
    if (cmp(current_element, pivot) < 0) {
      i++;
      quick_swap(base + i * element_size, current_element, element_size);
    }
  }
  quick_swap(base + (i + 1) * element_size, base + high * element_size,
             element_size);
  return (i + 1);
}

void quicksort_aux(void *arr, int low, int high, size_t element_size,
                   Comparator cmp) {
  if (low < high) {
    int pivot_index = partition(arr, low, high, element_size, cmp);
    quicksort_aux(arr, low, pivot_index - 1, element_size, cmp);
    quicksort_aux(arr, pivot_index + 1, high, element_size, cmp);
  }
}

void quicksort(void *arr, size_t size, size_t element_size, Comparator cmp) {
  quicksort_aux(arr, 0, size - 1, element_size, cmp);
}

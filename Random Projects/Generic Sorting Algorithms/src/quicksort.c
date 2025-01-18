#include "../libraries/quicksort.h"
#include "../libraries/swap.h"

int partition(void *arr, int low, int high, size_t element_size,
              Comparator cmp) {
  char *base = (char *)arr;
  void *pivot = base + high * element_size;
  int i = low - 1;

  for (int j = low; j < high; j++) {
    void *current_element = base + j * element_size;
    if (cmp(current_element, pivot) < 0) {
      i++;
      swap_elements(base + i * element_size, current_element, element_size);
    }
  }
  swap_elements(base + (i + 1) * element_size, base + high * element_size,
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

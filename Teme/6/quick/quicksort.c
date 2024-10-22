#include "quicksort.h"
#include <string.h>

// Utility function to swap two elements using memcpy
void swap(void *a, void *b, int element_size) {
  char temp[element_size];
  memcpy(temp, a, element_size);
  memcpy(a, b, element_size);
  memcpy(b, temp, element_size);
}

// Partition function for quicksort
int partition(void *arr, int low, int high, int element_size, Comparator comp) {
  char *base = (char *)arr;
  void *pivot = base + high * element_size; // Pivot element is the last element
  int i = low - 1;

  for (int j = low; j < high; j++) {
    void *current_element = base + j * element_size;
    if (comp(current_element, pivot) < 0) {
      i++;
      swap(base + i * element_size, current_element, element_size);
    }
  }
  swap(base + (i + 1) * element_size, base + high * element_size, element_size);
  return (i + 1);
}

// Recursive quicksort function
void quicksort(void *arr, int low, int high, int element_size, Comparator cmp) {
  if (low < high) {
    int pivot_index = partition(arr, low, high, element_size, cmp);

    // Recursively sort elements before and after partition
    quicksort(arr, low, pivot_index - 1, element_size, cmp);
    quicksort(arr, pivot_index + 1, high, element_size, cmp);
  }
}

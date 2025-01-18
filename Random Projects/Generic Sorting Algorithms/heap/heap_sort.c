#include "heap_sort.h"
#include <string.h>

typedef int (*Comparator)(const void *, const void *);

void heap_swap(void *a, void *b, size_t element_size) {
  char temp[element_size];
  memcpy(temp, a, element_size);
  memcpy(a, b, element_size);
  memcpy(b, temp, element_size);
}

// Heapify a subtree with root at index i in an array of num_elements elements
static void heapify(void *base, size_t num_elements, size_t element_size,
                    Comparator cmp, size_t i) {
  size_t largest = i; // Initialize largest as root
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;

  // Calculate addresses for comparison
  void *root = (char *)base + i * element_size;
  void *left_child = (char *)base + left * element_size;
  void *right_child = (char *)base + right * element_size;

  // Compare and find the largest
  if (left < num_elements && cmp(left_child, root) > 0)
    largest = left;

  if (right < num_elements &&
      cmp(right_child, (char *)base + largest * element_size) > 0)
    largest = right;

  if (largest != i) {
    // Swap if root is not largest
    heap_swap((char *)base + i * element_size,
              (char *)base + largest * element_size, element_size);
    // Heapify the affected subtree
    heapify(base, num_elements, element_size, cmp, largest);
  }
}

void heapsort(void *array, size_t size, size_t element_size, Comparator cmp) {
  char *arr = (char *)array;
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(arr, size, element_size, cmp, i);
  }

  for (int i = size - 1; i >= 0; i--) {
    heap_swap(arr, arr + i * element_size, element_size);
    heapify(arr, size, element_size, cmp, i);
  }
}

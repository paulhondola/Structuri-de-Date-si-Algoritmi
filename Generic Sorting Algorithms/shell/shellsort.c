#include "shellsort.h"
#include <string.h>

void swap(void *a, void *b, int element_size) {
  char temp[element_size];
  memcpy(temp, a, element_size);
  memcpy(a, b, element_size);
  memcpy(b, temp, element_size);
}

// Shell Sort implementation
void shellsort(void *arr, int array_size, int element_size, Comparator cmp,
               int gaps[], int number_of_gaps) {

  char *base = (char *)arr;

  // Loop over each gap in the gap sequence
  for (int g = number_of_gaps - 1; g >= 0; g--) {
    int gap = gaps[g];

    // Perform gapped insertion sort for this gap
    for (int i = gap; i < array_size; i++) {
      // Store the current element in a temporary buffer
      char temp[element_size];
      memcpy(temp, base + i * element_size, element_size);

      int j = i;
      // Shift elements of the sorted subarray until we find the correct
      // location for temp
      while (j >= gap && cmp(base + (j - gap) * element_size, temp) > 0) {
        // Move the previous element up by one gap
        memcpy(base + j * element_size, base + (j - gap) * element_size,
               element_size);
        j -= gap;
      }
      // Place the stored element in its correct position
      memcpy(base + j * element_size, temp, element_size);
    }
  }
}

void generate_gaps_fib(int gaps[], int *number_of_gaps, int array_size) {
  int index = 0;
  gaps[index++] = 1;
  gaps[index++] = 2;

  for (int i = 3; i < array_size / 2;) {
    gaps[index++] = i;
    i = gaps[index - 1] + gaps[index - 2];
  }

  *number_of_gaps = index;
}

void generate_gaps_shell(int gaps[], int *number_of_gaps, int array_size,
                         step_generator step) {
  int index = 0;
  for (int i = 1; i < array_size / 2;) {
    gaps[index++] = i;
    i = step(i);
  }

  *number_of_gaps = index;
}

#include "shellsort.h"

void shell_sort(void *arr[], int size, Comparator comp, int gaps[],
                int num_gaps) {

  // Loop over the gaps
  for (int g = num_gaps - 1; g >= 0; g--) {
    int gap = gaps[g];

    // Perform a gapped insertion sort for this gap
    for (int i = gap; i < size; i++) {
      void *temp = arr[i];
      int j;

      // Use the comparator to decide the order
      for (j = i; j >= gap && comp(arr[j - gap], temp) > 0; j -= gap) {
        arr[j] = arr[j - gap];
      }

      // Place temp (the original arr[i]) in its correct location
      arr[j] = temp;
    }
  }
}

void generate_gaps_via_step_function(int gaps[], int *gaps_size, int array_size,
                                     gap_step step) {

  int index = 0;
  for (int i = 1; i <= array_size / 2;) {
    gaps[index++] = i;
    i = step(i);
  }

  *gaps_size = index;
}

void generate_gaps_fib(int gaps[], int *gaps_size, int array_size) {
  int index = 0;
  gaps[index++] = 1;
  gaps[index++] = 2;
  for (int i = 3; i <= array_size / 2;) {
    gaps[index++] = i;
    i = gaps[index - 1] + gaps[index - 2];
  }
  *gaps_size = index;
}

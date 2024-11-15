#include "../libraries/shellsort.h"
#include <string.h>

void shellsort(void *arr, size_t array_size, size_t element_size,
               Comparator cmp, int gaps[], int number_of_gaps) {

  char *base = (char *)arr;

  for (int g = number_of_gaps - 1; g >= 0; g--) {
    int gap = gaps[g];

    for (size_t i = gap; i < array_size; i++) {
      char temp[element_size];
      // temp holds the current element
      memcpy(temp, base + i * element_size, element_size);

      // Insertion sort
      size_t j = i;
      while (j >= gap && cmp(temp, base + (j - gap) * element_size) < 0) {
        // copy the min element in the gapped array
        memcpy(base + j * element_size, base + (j - gap) * element_size,
               element_size);
        j -= gap;
      }
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

#include "merge.h"
#include <string.h>

void merge(void *merged, void *arr1, void *arr2, size_t *merged_size,
           size_t size1, size_t size2, size_t element_size) {

  size_t i = 0, j = 0, k = 0;

  while (i < size1 && j < size2) {
    if (memcmp(arr1 + i * element_size, arr2 + j * element_size, element_size) <
        0) {
      memcpy(merged + k * element_size, arr1 + i * element_size, element_size);
      i++;
    } else {
      memcpy(merged + k * element_size, arr2 + j * element_size, element_size);
      j++;
    }
    k++;
  }

  while (i < size1) {
    memcpy(merged + k * element_size, arr1 + i * element_size, element_size);
    i++;
    k++;
  }

  while (j < size2) {
    memcpy(merged + k * element_size, arr2 + j * element_size, element_size);
    j++;
    k++;
  }

  *merged_size = k;
}

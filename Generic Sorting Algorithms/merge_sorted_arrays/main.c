#include "merge.h"
#include <stdio.h>
int main(void) {
  int arr1[] = {1, 3, 5, 7, 9};
  int arr2[] = {2, 4, 6, 8, 10};
  int merged[10];
  size_t merged_size;

  merge(merged, arr1, arr2, &merged_size, 5, 5, sizeof(int));

  for (size_t i = 0; i < merged_size; i++) {
    printf("%d ", merged[i]);
  }
  printf("\n");

  return 0;
}

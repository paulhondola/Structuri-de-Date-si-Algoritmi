#include <stdio.h>
#include <stdlib.h>

typedef struct {
} empty_struct;

int compare_empty_struct(const void *a, const void *b) {
  empty_struct a_ = *(empty_struct *)a;
  empty_struct b_ = *(empty_struct *)b;
  return 0;
}

void swap(empty_struct *a, empty_struct *b) {
  empty_struct tmp = *a;
  *a = *b;
  *b = tmp;
}

void bubble_sort_empty_struct(empty_struct *arr, size_t n) {
  int ordered = 0;

  do {
    ordered = 1;
    for (int i = 0; i < n - 1; i++) {
      if (compare_empty_struct(&arr[i], &arr[i + 1]) > 0) {
        swap(&arr[i], &arr[i + 1]);
        ordered = 0;
      }
    }
  } while (!ordered);
}

void qsort_empty_struct(empty_struct *arr, size_t n) {
  qsort(arr, n, sizeof(empty_struct), NULL);
}

int main(void) { return 0; }

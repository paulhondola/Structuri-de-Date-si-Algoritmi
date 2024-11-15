#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Comparator for integers
int compare_int(const void *p, const void *q) {
  int a = *(int *)p;
  int b = *(int *)q;
  return (a > b) - (a < b); // Return -1, 0, or 1
}

// Comparator for floats
int compare_float(const void *p, const void *q) {
  float a = *(float *)p;
  float b = *(float *)q;
  return (a > b) - (a < b); // Return -1, 0, or 1
}

void integer_run_test(int size, int max_value) {

  int arr[size];
  for (int i = 0; i < size; i++) {
    arr[i] = rand() % max_value;
  }

  printf("Original integer array: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  quicksort(arr, size, sizeof(arr[0]), compare_int);

  printf("Sorted integer array: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void float_run_test(int size, int max_value) {

  float arr[size];
  for (int i = 0; i < size; i++) {
    arr[i] = (float)rand() / (float)(RAND_MAX / max_value);
  }

  printf("Original float array: ");
  for (int i = 0; i < size; i++) {
    printf("%.2f ", arr[i]);
  }
  printf("\n");

  quicksort(arr, size, sizeof(arr[0]), compare_float);

  printf("Sorted float array: ");
  for (int i = 0; i < size; i++) {
    printf("%.2f ", arr[i]);
  }
  printf("\n");
}

int main() {
  srand(time(NULL));

  integer_run_test(10, 100);
  float_run_test(10, 100);

  return 0;
}

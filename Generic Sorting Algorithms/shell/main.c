#include "shellsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Comparator function for integers
int compare_int(const void *p, const void *q) {
  int a = *(int *)p;
  int b = *(int *)q;
  return (a > b) - (a < b); // Return -1, 0, or 1
}

// Comparator function for floats
int compare_float(const void *p, const void *q) {
  float a = *(float *)p;
  float b = *(float *)q;
  return (a > b) - (a < b);
}

void integer_run_test(int size, int max_value, int gaps[], int number_of_gaps) {

  int arr[size];
  for (int i = 0; i < size; i++) {
    arr[i] = rand() % max_value;
  }

  printf("Original integer array: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  shellsort(arr, size, sizeof(arr[0]), compare_int, gaps, number_of_gaps);

  printf("Sorted integer array: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void float_run_test(int size, int max_value, int gaps[], int number_of_gaps) {

  float arr[size];
  for (int i = 0; i < size; i++) {
    arr[i] = (float)rand() / (float)(RAND_MAX / max_value);
  }

  printf("Original float array: ");
  for (int i = 0; i < size; i++) {
    printf("%.2f ", arr[i]);
  }
  printf("\n");

  shellsort(arr, size, sizeof(arr[0]), compare_float, gaps, number_of_gaps);

  printf("Sorted float array: ");
  for (int i = 0; i < size; i++) {
    printf("%.2f ", arr[i]);
  }
  printf("\n");
}

int step(int n) { return 3 * n + 1; }

void run_test(int size, int gaps[], int number_of_gaps) {
  printf("--------------\nGAPS FIB: ");
  for (int i = 0; i < number_of_gaps; i++)
    printf("%d ", gaps[i]);
  printf("\n--------------\n");

  integer_run_test(size, size, gaps, number_of_gaps);
  float_run_test(size, size, gaps, number_of_gaps);
}

#define SIZE 100
int main() {

  int gaps_fib[SIZE];
  int number_of_gaps_fib = 0;

  int gaps_shell[SIZE];
  int number_of_gaps_shell = 0;

  generate_gaps_fib(gaps_fib, &number_of_gaps_fib, SIZE);

  generate_gaps_shell(gaps_shell, &number_of_gaps_shell, SIZE, step);

  run_test(SIZE, gaps_fib, number_of_gaps_fib);
  // run_test(SIZE, gaps_shell, number_of_gaps_shell);

  return 0;
}

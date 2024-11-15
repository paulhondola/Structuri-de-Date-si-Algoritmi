#include "../libraries/bubblesort.h"
#include "../libraries/heap_sort.h"
#include "../libraries/insertionsort.h"
#include "../libraries/quicksort.h"
#include "../libraries/selectionsort.h"
#include "../libraries/shellsort.h"
#include "../libraries/timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*sort_fn)(void *, size_t, size_t, Comparator);

typedef void (*sort_shell)(void *, size_t, size_t, Comparator, step_generator);

int step(int n) { return 3 * n + 1; }

int compare_int(const void *p, const void *q) {
  int a = *(int *)p;
  int b = *(int *)q;
  return (a > b) - (a < b);
}

void generate_random_int_array(int arr[], size_t size, size_t lower_bound,
                               size_t upper_bound) {
  for (size_t i = 0; i < size; i++) {
    arr[i] = lower_bound + rand() % (upper_bound - lower_bound);
  }
}

double test_shell(int arr[], size_t size, step_generator step) {
  double time = start();

  int gap_count = 0;
  int gaps[size / 4];

  generate_gaps_shell(gaps, &gap_count, size, step);

  shellsort(arr, size, sizeof(arr[0]), compare_int, gaps, gap_count);

  time = stop();
  return time;
}

double test(int arr[], size_t size, sort_fn sort_fn) {
  double time = start();
  sort_fn(arr, size, sizeof(arr[0]), compare_int);
  time = stop();
  return time;
}

void test_run(int arr[], size_t size) {

  generate_random_int_array(arr, size, 0, 1000);
  double bubble_time = test(arr, size, bubblesort);
  printf("Bubble sort: %lf\n", bubble_time);

  generate_random_int_array(arr, size, 0, 1000);
  double insertion_time = test(arr, size, insertionsort);
  printf("Insertion sort: %lf\n", insertion_time);

  generate_random_int_array(arr, size, 0, 1000);
  double selection_time = test(arr, size, selectionsort);
  printf("Selection sort: %lf\n", selection_time);

  generate_random_int_array(arr, size, 0, 1000);
  double shell_time = test_shell(arr, size, step);
  printf("Shell sort: %lf\n", shell_time);

  generate_random_int_array(arr, size, 0, 1000);
  double quick_time = test(arr, size, quicksort);
  printf("Quick sort: %lf\n", quick_time);

  generate_random_int_array(arr, size, 0, 1000);
  double heap_time = test(arr, size, heap_sort);
  printf("Heap sort: %lf\n", heap_time);
}

int main(void) {
  srand(time(NULL));

  const size_t size = 20000;
  int arr[size];

  test_run(arr, size);

  return 0;
}

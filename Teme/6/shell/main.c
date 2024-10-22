#include "shellsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int key, value;
} KV_Pair;

int gap_step_1(int n) { return 3 * n + 1; }

void init_fib(const int size, KV_Pair data[], void *arr[], int gaps[],
              int *num_gaps, gap_generator gen_gaps) {
  int max_key = size / 2;
  int max_value = size / 2;

  // Fill the array with random integers
  // Create an array of void pointers pointing to the integer data
  for (int i = 0; i < size; i++) {
    data[i].key = rand() % max_key;
    data[i].value = rand() % max_value;
    arr[i] = &data[i];
  }

  gen_gaps(gaps, num_gaps, size);
}

void init_custom(const int size, KV_Pair data[], void *arr[], int gaps[],
                 int *num_gaps, custom_gap_generator gen_gaps, gap_step step) {

  int max_key = size / 2;
  int max_value = size / 2;

  // Fill the array with random integers
  // Create an array of void pointers pointing to the integer data
  for (int i = 0; i < size; i++) {
    data[i].key = rand() % max_key;
    data[i].value = rand() % max_value;
    arr[i] = &data[i];
  }

  gen_gaps(gaps, num_gaps, size, gap_step_1);
}

// Function to compare integers (ascending order)
int compare_KV_by_key(const void *a, const void *b) {
  // Dereference the void pointers and compare the integer values
  int key_diff = ((KV_Pair *)a)->key - ((KV_Pair *)b)->key;
  int value_diff = ((KV_Pair *)a)->value - ((KV_Pair *)b)->value;
  return key_diff != 0 ? key_diff : value_diff;
}

int compare_KV_by_value(const void *a, const void *b) {
  // Dereference the void pointers and compare the integer values
  int key_diff = ((KV_Pair *)a)->key - ((KV_Pair *)b)->key;
  int value_diff = ((KV_Pair *)a)->value - ((KV_Pair *)b)->value;
  return value_diff != 0 ? value_diff : key_diff;
}

// Function to print a KV_Pair
void print_KV(void *pair) {
  KV_Pair *p = (KV_Pair *)pair;
  printf("(%d, %d)\n", p->key, p->value);
}

// Function to print an array of integers
void print_KV_array(void *arr[], int size) {
  for (int i = 0; i < size; i++) {
    print_KV(arr[i]);
  }
}

void custom_run(KV_Pair data[], const int SIZE) {
  void *arr[SIZE];
  int gaps[SIZE];
  int num_gaps = 0;

  init_fib(SIZE, data, arr, gaps, &num_gaps, generate_gaps_fib);

  // Check the gaps
  printf("Gaps used: ");
  for (int i = 0; i < num_gaps; i++) {
    printf("%d ", gaps[i]);
  }
  printf("\n");

  // Testing
  printf("Array before sorting:\n");
  print_KV_array(arr, SIZE);

  // Sort the array using the shellSort function and compareInt comparator
  shell_sort(arr, SIZE, compare_KV_by_key, gaps, num_gaps);

  printf("Array after sorting:\n");
  print_KV_array(arr, SIZE);
}

void fib_run(KV_Pair data[], const int SIZE) {
  void *arr[SIZE];
  int gaps[SIZE];
  int num_gaps = 0;

  init_custom(SIZE, data, arr, gaps, &num_gaps, generate_gaps_via_step_function,
              gap_step_1);

  // Check the gaps
  printf("Gaps used: ");
  for (int i = 0; i < num_gaps; i++) {
    printf("%d ", gaps[i]);
  }
  printf("\n");

  // Testing
  printf("Array before sorting:\n");
  print_KV_array(arr, SIZE);

  // Sort the array using the shellSort function and compareInt comparator
  shell_sort(arr, SIZE, compare_KV_by_key, gaps, num_gaps);

  printf("Array after sorting:\n");
  print_KV_array(arr, SIZE);
}

// Main function to test the shellSort function with integers
int main(void) {

  srand(time(NULL));

  const int SIZE = 20;
  KV_Pair data[SIZE];

  fib_run(data, SIZE);

  return 0;
}

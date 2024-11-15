#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
  int key, value;
} data_t;

void swap(void *a, void *b) {
  data_t temp = *(data_t *)a;
  *(data_t *)a = *(data_t *)b;
  *(data_t *)b = temp;
}
int comparator(const void *a, const void *b) {
  data_t data_a = *(data_t *)a;
  data_t data_b = *(data_t *)b;
  if (data_a.key == data_b.key)
    return data_a.value - data_b.value;
  else
    return data_a.key - data_b.key;
}

void insertion_sort(data_t arr[], size_t size) {
  for (int i = 0; i < size - 1; i++) {
    int index = i;
    for (int j = i + 1; j < size; j++)
      if (comparator(&arr[j], &arr[index]) < 0)
        index = j;

    swap(&arr[i], &arr[index]);
  }
}

void print_struct_element(data_t data) {
  printf("key: %d, value: %d\n", data.key, data.value);
}

void print(data_t arr[], size_t SIZE) {
  for (int i = 0; i < SIZE - 1; i++)
    print_struct_element(arr[i]);
}

int main(void) {

  srand(time(NULL));

  const int SIZE = 1000;

  data_t arr[SIZE];
  for (int i = 0; i < SIZE; i++)
    arr[i].key = rand() % SIZE, arr[i].value = i;

  insertion_sort(arr, SIZE);

  print(arr, SIZE);

  return 0;
}

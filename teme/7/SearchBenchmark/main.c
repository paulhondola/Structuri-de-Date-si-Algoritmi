#include "timer.h"
#include "array_generator.h"
#include "search.h"
#include <time.h>

void free_datatype_array(data_t *arr, const size_t size) {
  for(size_t i = 0; i < size; i++)
    free_datatype(arr[i]);
  free(arr);
}

void benchmark(const size_t size, search_fn search, const unsigned target, FILE *file){
  data_t *arr = generate_asc_array(size);

  // BENCHMARK SEARCH
  double time = start();
  search(arr, size, target);
  time = stop();

  fprintf(file, "%zu %lf\n", size, time);

  free_datatype_array(arr, size);
}

int main(void) {

  // PARAMETERS
  srand(time(NULL));
  const int SIZE = 10000000;
  const int CNT = 10;

  // OPEN FILES
  FILE *linear_benchmark_file = fopen("linear_benchmark.txt", "w");
  FILE *binary_benchmark_file = fopen("binary_benchmark.txt", "w");
  FILE *interpolation_benchmark_file = fopen("interpolation_benchmark.txt", "w");

  // RUN BENCHMARK
  for(size_t i = 1; i <= CNT; i++)
  {
    printf("Run %zu\n", i);
    unsigned target = UINT32_MAX;
    const size_t size = i * SIZE;

    benchmark(size, linear_search, target, linear_benchmark_file);
    printf("Linear search done\n");

    benchmark(size, binary_search, target, binary_benchmark_file);
    printf("Binary search done\n");

    benchmark(size, interpolation_search, target, interpolation_benchmark_file);
    printf("Interpolation search done\n");
  }

  // CLOSE FILES
  fclose(linear_benchmark_file);
  fclose(binary_benchmark_file);
  fclose(interpolation_benchmark_file);

  return 0;
}

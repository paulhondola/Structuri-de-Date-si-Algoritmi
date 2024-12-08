#include "array_generator.h"

data_t *generate_asc_array(const size_t size) {
    data_t *arr = malloc(size * sizeof(data_t));
    arr[0] = get_datatype(0);
    for (size_t i = 1; i < size; i++)
        arr[i] = get_datatype(get_key(arr[i - 1]) + 1);
    return arr;
}

void print_array(const data_t *arr, const size_t size, FILE *file) {
    for (size_t i = 0; i < size; i++)
        print_datatype(arr[i], file);
    fprintf(file, "\n");
}
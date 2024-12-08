#ifndef __SEARCH_H
#define __SEARCH_H
#include "datatype.h"

typedef int (*search_fn)(const data_t *, size_t, int);

int linear_search(const data_t *arr, size_t size, int target);
int binary_search(const data_t *arr, size_t size, int target);
int interpolation_search(const data_t *arr, size_t size, int target);

#endif
#ifndef __QUICKSORT_H
#define __QUICKSORT_H
#include <stddef.h>

void quicksort(void *arr, size_t size, size_t element_size,
               int (*Comparator)(const void *, const void *));

#endif

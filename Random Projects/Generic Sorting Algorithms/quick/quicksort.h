#ifndef __QUICKSORT_H
#define __QUICKSORT_H
#include <stddef.h>

typedef int (*Comparator)(const void *, const void *);

void quicksort(void *arr, size_t size, size_t element_size, Comparator cmp);

#endif

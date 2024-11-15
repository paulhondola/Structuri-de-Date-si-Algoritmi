#ifndef __SELECTIONSORT_H
#define __SELECTIONSORT_H
#include <stddef.h>

void selectionsort(void *array, size_t array_size, size_t element_size,
                   int (*Comparator)(const void *, const void *));

#endif

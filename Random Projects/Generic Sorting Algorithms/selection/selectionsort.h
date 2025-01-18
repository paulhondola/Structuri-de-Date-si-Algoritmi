#ifndef __SELECTIONSORT_H
#define __SELECTIONSORT_H
#include <stddef.h>

typedef int (*Comparator)(const void *, const void *);

void selectionsort(void *array, size_t array_size, size_t element_size,
                   Comparator cmp);

#endif

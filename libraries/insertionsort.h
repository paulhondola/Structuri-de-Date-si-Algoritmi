#ifndef __INSERTIONSORT_H
#define __INSERTIONSORT_H
#include <stddef.h>

void insertionsort(void *array, size_t array_size, size_t element_size,
                   int (*Comparator)(const void *, const void *));

#endif

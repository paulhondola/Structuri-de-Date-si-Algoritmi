#ifndef __BUBBLESORT_H
#define __BUBBLESORT_H
#include <stddef.h>

void bubblesort(void *array, size_t array_size, size_t element_size,
                int (*Comparator)(const void *, const void *));

#endif

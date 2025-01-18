#ifndef __HEAP_SORT_H
#define __HEAP_SORT_H

#include <stddef.h>

void heap_sort(void *array, size_t size, size_t element_size,
               int (*Comparator)(const void *, const void *));

#endif

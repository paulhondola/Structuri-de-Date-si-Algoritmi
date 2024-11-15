#ifndef __MERGE_H
#define __MERGE_H

#include <stddef.h>
void merge(void *merged, void *arr1, void *arr2, size_t *merged_size,
           size_t size1, size_t size2, size_t element_size);

#endif

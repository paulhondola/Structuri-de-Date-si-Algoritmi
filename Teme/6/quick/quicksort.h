#ifndef __QUICKSORT_H
#define __QUICKSORT_H

typedef int (*Comparator)(const void *p, const void *q);

void quicksort(void *arr, int low, int high, int element_size, Comparator cmp);

#endif

#ifndef __BUBBLESORT_H
#define __BUBBLESORT_H

typedef int (*Comparator)(const void *p, const void *q);

void bubblesort(void *array, int array_size, int element_size, Comparator cmp);

#endif

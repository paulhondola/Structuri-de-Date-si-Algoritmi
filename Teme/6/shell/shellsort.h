#ifndef __SHELLSORT_H
#define __SHELLSORT_H

typedef int (*Comparator)(const void *, const void *);

typedef int (*step_generator)(int);

void shellsort(void *arr, int array_size, int element_size, Comparator cmp,
               int gaps[], int number_of_gaps);

void generate_gaps_fib(int gaps[], int *number_of_gaps, int array_size);

void generate_gaps_shell(int gaps[], int *number_of_gaps, int array_size,
                         step_generator step);
#endif

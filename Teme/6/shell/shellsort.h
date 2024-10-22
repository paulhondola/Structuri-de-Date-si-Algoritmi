#ifndef __SHELLSORT_H
#define __SHELLSORT_H

// Comparator function type that accepts void pointers to be casted and compared
typedef int (*Comparator)(const void *, const void *);

// Gap generator function type that accepts the gap array, the number of gaps,
// and the size of the array to be sorted
typedef void (*gap_generator)(int[], int *, int);

// the function type for the gap stepping function: (3 * n + 1) for example
typedef int (*gap_step)(int);
typedef void (*custom_gap_generator)(int[], int *, int, gap_step);

// Generates the gaps for the shell sort algorithm using a step function
void generate_gaps_via_step_function(int gaps[], int *gaps_size, int array_size,
                                     gap_step step);

// Generates the gaps for the shell sort algorithm using the Fibonacci
// sequence
void generate_gaps_fib(int gaps[], int *gaps_size, int array_size);

// Sorts the array using the shell sort algorithm
void shell_sort(void *arr[], int size, Comparator comp, int gaps[],
                int num_gaps);

#endif

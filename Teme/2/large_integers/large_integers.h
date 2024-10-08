#ifndef __LARGE_INTEGERS_H
#define __LARGE_INTEGERS_H
#include <stdbool.h>
#include <stdio.h>

typedef struct LARGE_INT *large_int;

large_int create(char *string);
void destroy(large_int number);

void print(large_int number, FILE *file);

large_int add(large_int a, large_int b);
bool greater(large_int a, large_int b);

#endif

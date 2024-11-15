#ifndef __MULTIME_H
#define __MULTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10000
#define MAX_NAME_LENGTH 200

typedef struct SET *set;

set init(char *name, size_t size, size_t max_value);
void show_elements(set my_set, FILE *file);
void show_data(set my_set, FILE *file);
set get_intersection(set set1, set set2, FILE *file);
int *get_biggest2(set my_set);
void destroy(set my_set);

#endif

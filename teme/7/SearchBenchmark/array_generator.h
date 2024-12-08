#ifndef __ARRAY_GENERATOR_H
#define __ARRAY_GENERATOR_H
#include "datatype.h"
#include <stdio.h>

data_t *generate_asc_array(size_t size);
void print_array(const data_t *arr, size_t size, FILE *file);

#endif
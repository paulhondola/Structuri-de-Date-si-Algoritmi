#ifndef __DATATYPE_H
#define __DATATYPE_H
#include <stdio.h>
#include <stdlib.h>

// Define the datatype
typedef struct DATATYPE *data_t;

// Getters
data_t get_datatype(unsigned key);
unsigned get_key(data_t data);

// Destructor
void free_datatype(data_t data);

// Debug
void print_datatype(data_t data, FILE *file);

#endif

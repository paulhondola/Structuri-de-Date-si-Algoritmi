// Helper functions for main

#ifndef EMACS2_H
#define EMACS2_H

// Dependencies
#include "../io_op/io_op.h"

// Constants
#define MAX_OPERATIONS 100

// Operations
void read_operations(operation ops[], int *op_count, FILE *file);
void print_operations(operation ops[], int op_count, FILE *file);
void execute_operations(list list, operation ops[], int op_count, FILE *file);
void free_operations(operation ops[], int op_count);

#endif //EMACS2_H

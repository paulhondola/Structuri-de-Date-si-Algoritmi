// Dependencies
#include "emacs2.h"
#include <stdlib.h>

void read_operations(operation ops[], int *op_count, FILE *file){
    fprintf(file, "Operations read: %d\n----------------------------\n", *op_count);
    for (int i = 0; i < MAX_OPERATIONS; i++){
        ops[i] = READ_OPERATION(file);
        if (ops[i] == NULL){
            *op_count = i;
            return;
        }

        if (IS_INVALID(ops[i])){
            FREE_OPERATION(ops[i]);
            i--;
        }
    }
}

void print_operations(operation ops[], int op_count, FILE *file){
    for (int i = 0; i < op_count; i++){
        PRINT_OPERATION(ops[i], file);
    }
}

void execute_operations(list list, operation ops[], int op_count, FILE *file){
    for (int i = 0; i < op_count; i++){
        EXECUTE_OPERATION(list, ops[i], file);
    }
}

void free_operations(operation ops[], int op_count){
    for (int i = 0; i < op_count; i++){
        FREE_OPERATION(ops[i]);
    }
}
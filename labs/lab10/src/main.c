#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "operations.h"

#define MAX_OPERATIONS 100

void read_operations(operation ops[], int *op_count, FILE *file){
    fprintf(file, "Operations read: %d\n----------------------------\n", *op_count);
    for (int i = 0; i < MAX_OPERATIONS; i++){
        ops[i] = READ_OPERATION(file);
        if (ops[i] == NULL){
            *op_count = i;
            return;
        }

        if (IS_INVALID(ops[i])){
            free(ops[i]);
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

int main(void){
    FILE *file = fopen("operations/operations.txt", "r");
    if (file == NULL){
        fprintf(stderr, "Error: Could not open file operations.txt");
        return 1;
    }

    FILE *log = fopen("operations/log", "w");
    if (log == NULL){
        fprintf(stderr, "Error: Could not open file log.txt");
        return 1;
    }

    list list = INIT_LIST();

    operation ops[MAX_OPERATIONS];
    int op_count = 0;

    read_operations(ops, &op_count, file);
    print_operations(ops, op_count, log);
    execute_operations(list, ops, op_count, log);

    free_operations(ops, op_count);
    DESTROY_LIST(list);

    fclose(file);
    fclose(log);

    return 0;
}
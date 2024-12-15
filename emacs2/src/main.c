#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100
#include "lib/emacs2/emacs2.h"

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

    list list = init_list();

    operation ops[MAX_OPERATIONS];
    int op_count = 0;

    read_operations(ops, &op_count, file);
    print_operations(ops, op_count, log);
    execute_operations(list, ops, op_count, log);

    free_operations(ops, op_count);
    destroy_list(list);

    fclose(file);
    fclose(log);

    return 0;
}
// Used for reading, writing and executing operations from operations file

#ifndef __OPERATIONS_H
#define __OPERATIONS_H

// Dependencies
#include "../file_op/file_op.h"

// Constants
#define MAX_FILE_NAME_LEN 128
#define MAX_WRITE_LEN 1024
#define MAX_INSERT_LEN 1024

// Structs
typedef struct OPERATION *operation;

// Operations
operation READ_OPERATION(FILE *);
int IS_INVALID(operation);
void PRINT_OPERATION(operation, FILE *);
void EXECUTE_OPERATION(list, operation, FILE *);
void FREE_OPERATION(operation);

#endif

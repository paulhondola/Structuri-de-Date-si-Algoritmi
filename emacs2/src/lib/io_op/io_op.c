#include "io_op.h"
#include <string.h>
#include <stdlib.h>

#define MAX_OPCODE_LEN 16
#define MAX_LINE_LEN 4096

// Structs for defining parameters of operations
typedef struct{} OPEN_OP;

typedef struct{} PRINT_OP;

typedef struct{
    int index;
    char *content;
} WRITE_OP;

typedef struct{
    int index;
    int count;
} DELETE_OP;

typedef struct{
    char *destination;
} SAVEAS_OP;

typedef struct{
    char *destination;
} COPY_OP;

// Struct for defining operations
struct OPERATION{
    enum{_INVALID = -1, _OPEN, _COPY, _SAVEAS, _WRITE, _DELETE, _PRINT, _PRINT_ALL} opcode;
    char *source;
    union
    {
        OPEN_OP open;
        PRINT_OP print;
        WRITE_OP write;
        DELETE_OP delete;
        SAVEAS_OP saveas;
        COPY_OP copy;
    };
};

// Operation functions
operation READ_OPERATION(FILE *file){
    char line[MAX_LINE_LEN];

    // check if the file is empty
    if(fgets(line, MAX_LINE_LEN, file) == NULL){
        return NULL;
    }

    // check newline character
    if (line[0] == '\n'){
        return READ_OPERATION(file);
    }

    operation op = malloc(sizeof(struct OPERATION));

    // tokenize the line
    char *token = strtok(line, " \n");

    // get opcode
    char opcode[MAX_OPCODE_LEN];
    strncpy(opcode, token, MAX_OPCODE_LEN);

    // PRINT_ALL has only one argument
    if (strcmp(opcode, "PRINT_ALL") == 0){
        op->opcode = _PRINT_ALL;
        return op;
    }

    // get source
    token = strtok(NULL, " \n");

    op->source = malloc(MAX_FILE_NAME_LEN);
    strncpy(op->source, token, MAX_FILE_NAME_LEN);
    token = strtok(NULL, " \n");

    // if the opcode is OPEN / PRINT -> return

    if (strcmp(opcode, "OPEN") == 0){
        op->opcode = _OPEN;
        return op;
    }

    if (strcmp(opcode, "PRINT") == 0){
        op->opcode = _PRINT;
        return op;
    }

    // if the opcode is SAVEAS / COPY -> get destination
    if (strcmp(opcode, "SAVEAS") == 0){
        op->opcode = _SAVEAS;
        op->saveas.destination = malloc(MAX_FILE_NAME_LEN);
        strncpy(op->saveas.destination, token, MAX_FILE_NAME_LEN);
        return op;
    }

    if (strcmp(opcode, "COPY") == 0){
        op->opcode = _COPY;
        op->copy.destination = malloc(MAX_FILE_NAME_LEN);
        strncpy(op->copy.destination, token, MAX_FILE_NAME_LEN);
        return op;
    }

    // if the opcode is WRITE -> get index and content
    if (strcmp(opcode, "WRITE") == 0){
        op->opcode = _WRITE;
        op->write.index = atoi(token);
        token = strtok(NULL, " \n");
        op->write.content = malloc(MAX_WRITE_LEN);
        strncpy(op->write.content, token, MAX_WRITE_LEN);
        return op;
    }

    // if the opcode is DELETE -> get index and count
    if (strcmp(opcode, "DELETE") == 0){
        op->opcode = _DELETE;
        op->delete.index = atoi(token);
        token = strtok(NULL, " \n");
        op->delete.count = atoi(token);
        return op;
    }

    op->opcode = _INVALID;
    return op;
}

int IS_INVALID(operation op){
    return op->opcode == _INVALID;
}

void PRINT_OPERATION(operation op, FILE *file){
    if (op == NULL){
        fprintf(file, "NO OPERATION\n");
        return;
    }

    switch(op->opcode){
    case _OPEN:
        fprintf(file, "OPEN %s\n", op->source);
        break;
    case _PRINT:
        fprintf(file, "PRINT %s\n", op->source);
        break;
    case _PRINT_ALL:
        fprintf(file, "PRINT_ALL\n");
        break;
    case _WRITE:
        fprintf(file, "WRITE %s %d %s\n", op->source, op->write.index, op->write.content);
        break;
    case _DELETE:
        fprintf(file, "DELETE %s %d %d\n", op->source, op->delete.index, op->delete.count);
        break;
    case _SAVEAS:
        fprintf(file, "SAVEAS %s %s\n", op->source, op->saveas.destination);
        break;
    case _COPY:
        fprintf(file, "COPY %s %s\n", op->source, op->copy.destination);
        break;
    case _INVALID:
        fprintf(file, "INVALID OPERATION\n");
        break;
    }
}

void EXECUTE_OPERATION(list list, operation op, FILE *file){
    switch (op->opcode){
    case _OPEN:
        OPEN(list, op->source);
        break;
    case _PRINT:
        PRINT(op->source, file);
        break;
    case _PRINT_ALL:
        PRINT_ALL(list, file);
        break;
    case _WRITE:
        WRITE(op->source, op->write.index, op->write.content);
        break;
    case _DELETE:
        DELETE(op->source, op->delete.index, op->delete.count);
        break;
    case _SAVEAS:
        SAVEAS(list, op->source, op->saveas.destination);
        break;
    case _COPY:
        COPY(op->source, op->copy.destination);
        break;
    case _INVALID:
        break;
    }
}

void FREE_OPERATION(operation op){
    if (IS_INVALID(op)){
        free(op);
        return;
    }

    if(op->source != NULL){
        free(op->source);
    }

    switch (op->opcode)
    {
    case _WRITE:
        free(op->write.content);
        break;
    case _SAVEAS:
        free(op->saveas.destination);
        break;
    case _COPY:
        free(op->copy.destination);
        break;
    default:
        break;
    }

    free(op);
}

// Used for reading, writing, copying, deleting, and saving files

#ifndef FILE_OP_H
#define FILE_OP_H

// Dependencies
#include <stdio.h>
#include "../list/list.h"

// Operations
int OPEN(list, const char *);

void WRITE(const char *, int, const char *);
void DELETE(const char *, int, int);

int COPY(const char *, const char *);
int SAVEAS(list, const char *, const char *);

int PRINT(const char *, FILE *);
void PRINT_ALL(list, FILE *);

void REMOVE_ALL(list);

#endif //FILE_OP_H

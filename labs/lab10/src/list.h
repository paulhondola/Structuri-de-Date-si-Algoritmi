#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>

// Constants
#define MAX_FILE_NAME_SIZE 128
#define MAX_FILE_CONTENT_SIZE 4096

// Structures
typedef struct LIST *list;

// Constructors
list INIT_LIST(void);

// Destructors
void DESTROY_LIST(list);
void REMOVE_ALL(list);

// deschide un fisier si il adauga la coada listei
int OPEN(list, const char*);

// scrie (insereaza) cuvantul <word> la indexul <index> in text. <word> nu contine spatii
void WRITE(const char *, int, const char *);

// sterge <count> caractere incepand de la <index>
void DELETE(const char *, int index, int count);

// printeaza numele fisierului si continutul fisierului
int PRINT(const char*, FILE *);

// printeaza numele tuturor fisierelor din lista si continutul lor
void PRINT_ALL(list, FILE *);

// inchide(elimina din lista) si salveaza fisierul <filename> ca si alt fisier numit <newname>
int SAVEAS(list, const char* src, const char* dst);

// copiaza fisierul <src> in fisierul <dst>
int COPY(const char* src, const char* dst);

#endif

//
// Created by Paul Hondola on 28.11.2024.
//

#ifndef MULTILIST_H
#define MULTILIST_H

#include <stdio.h>

typedef struct NODE *node;
typedef struct LIST *list;
typedef struct MULTILIST *multilist;

// Constructors
node init_node(void *data);
list init_list();
multilist init_multilist();

// Checkers
int list_is_empty(list l);
int multilist_is_empty(multilist ml);

// Selectors
node select_node(list l, int index);
list select_list(multilist ml, int index);

// Adders
void add_node_to_list_front(list l, node n);
void add_node_to_list_back(list l, node n);
void add_list_to_multilist_front(multilist ml, list l);
void add_list_to_multilist_back(multilist ml, list l);
void add_node_to_multilist_front(multilist ml, node n, int index);
void add_node_to_multilist_back(multilist ml, node n, int index);

// Setters
void set_data(node n, void *data);

// Getters
void *get_data(node n);
node get_list_head(list l);
node get_list_tail(list l);
list get_multilist_head(multilist ml);
list get_multilist_tail(multilist ml);

// Destructors
void destroy_node(node n);
void destroy_list(list l);
void destroy_multilist(multilist ml);

// Debug
typedef void (*print_fn) (void *data, FILE *file);
void print_node(node n, FILE *file, print_fn);
void print_list(list l, FILE *file, print_fn);
void print_multilist(multilist ml, FILE *file, print_fn);

#endif //MULTILIST_H

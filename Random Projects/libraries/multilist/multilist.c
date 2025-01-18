//
// Created by Paul Hondola on 28.11.2024.
//
#include <stdlib.h>
#include "multilist.h"

struct NODE{
    void *data;
    struct NODE *next;
    struct NODE *prev;
};

struct LIST{
    struct NODE *head;
    struct NODE *tail;
    struct LIST *next;
    struct LIST *prev;
};

struct MULTILIST{
    struct LIST *head;
    struct LIST *tail;
};

// Constructors
node init_node(void *data){
    node new_node = malloc(sizeof(struct NODE));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

list init_list(){
    list new_list = malloc(sizeof(struct LIST));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->next = NULL;
    new_list->prev = NULL;
    return new_list;
}

multilist init_multilist(){
    multilist new_multilist = malloc(sizeof(struct MULTILIST));
    new_multilist->head = NULL;
    new_multilist->tail = NULL;
    return new_multilist;
}

// Checkers
int list_is_empty(list l){
    return l->head == NULL;
}

int multilist_is_empty(multilist ml){
    return ml->head == NULL;
}

// Selectors
node select_node(list l, int index){
    node current = l->head;
    for (int i = 0; i < index; i++){
        if (current == NULL){
            return NULL;
        }
        current = current->next;
    }
    return current;
}

list select_list(multilist ml, int index){
    list current = ml->head;
    for (int i = 0; i < index; i++){
        if (current == NULL){
            return NULL;
        }
        current = current->next;
    }
    return current;
}

// Adders
void add_node_to_list_front(list l, node n){
    if (list_is_empty(l)){
        l->head = n;
        l->tail = n;
    } else {
        l->head->prev = n;
        n->next = l->head;
        l->head = n;
    }
}

void add_node_to_list_back(list l, node n){
    if (list_is_empty(l)){
        l->head = n;
        l->tail = n;
    } else {
        l->tail->next = n;
        n->prev = l->tail;
        l->tail = n;
    }

}

void add_list_to_multilist_front(multilist ml, list l){
    if (multilist_is_empty(ml)){
        ml->head = l;
        ml->tail = l;
    } else {
        ml->head->prev = l;
        l->next = ml->head;
        ml->head = l;
    }
}

void add_list_to_multilist_back(multilist ml, list l){
    if (multilist_is_empty(ml)){
        ml->head = l;
        ml->tail = l;
    } else {
        ml->tail->next = l;
        l->prev = ml->tail;
        ml->tail = l;
    }
}

void add_node_to_multilist_front(multilist ml, node n, int index){
    add_node_to_list_front(select_list(ml, index), n);
}

void add_node_to_multilist_back(multilist ml, node n, int index){
    add_node_to_list_back(select_list(ml, index), n);
}

// Setters
void set_data(node n, void *data){
    n->data = data;
}

// Getters
void *get_data(node n){
    return n->data;
}

node get_list_head(list l){
    return l->head;
}

node get_list_tail(list l){
    return l->tail;
}

list get_multilist_head(multilist ml){
    return ml->head;
}

list get_multilist_tail(multilist ml){
    return ml->tail;
}

// Destructors
void destroy_node(node n){
    free(n->data);
    free(n);
}

void destroy_list(list l){
    node current = l->head;
    while(current != NULL){
        node next = current->next;
        destroy_node(current);
        current = next;
    }
    free(l);
}

void destroy_multilist(multilist ml){
    list current = ml->head;
    while(current != NULL){
        list next = current->next;
        destroy_list(current);
        current = next;
    }
    free(ml);
}

// Debug
void print_node(node n, FILE *file, print_fn fp){
    fp(n->data, file);
}

void print_list(list l, FILE *file, print_fn fp){
    node current = l->head;
    while(current != NULL){
        print_node(current, file, fp);
        fprintf(file, " -> ");
        current = current->next;
    }
    fprintf(file, "NULL");
}

void print_multilist(multilist ml, FILE *file, print_fn fp){
    list current = ml->head;
    while(current != NULL){
        print_list(current, file, fp);
        fprintf(file, "\n|\n");
        current = current->next;
    }
    fprintf(file, "NULL");
}
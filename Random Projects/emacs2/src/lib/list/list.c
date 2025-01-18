// Dependencies
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Structures
struct NODE
{
  char filename[MAX_FILE_NAME_SIZE];
  struct NODE *next;
};

struct LIST
{
  struct NODE *head;
  struct NODE *rear;
};

// Constructors
node init_node(const char *filename){
  node new_node = malloc(sizeof(struct NODE));
  if (new_node == NULL)
    return NULL;

  strncpy(new_node->filename, filename, MAX_FILE_NAME_SIZE);
  new_node->next = NULL;
  return new_node;
}

list init_list(void){
  list new_list = malloc(sizeof(struct LIST));
  if (new_list == NULL)
    return NULL;

  new_list->head = NULL;
  new_list->rear = NULL;
  return new_list;
}

// Destructors - free memory
void destroy_node(node node){
  if(node == NULL){
    fprintf(stderr, "Error: Node is not initialized or already freed\n");
    return;
  }
  free(node);
}

void destroy_list(list list){
  if(list == NULL){
    fprintf(stderr, "Error: List is not initialized or already freed\n");
    return;
  }

  node current = list->head;
  while(current != NULL){
    node next = current->next;
    destroy_node(current);
    current = next;
  }
  free(list);
}

// Add to back of list
int add_node(list list, const char *filename){
  node new_node = init_node(filename);
  if (new_node == NULL || list == NULL)
    return 0;

  if (list->head == NULL){
    list->head = new_node;
    list->rear = new_node;
  } else {
    list->rear->next = new_node;
    list->rear = new_node;
  }
  return 1;
}

// Check if filename is the same
int check_filename(const char *current, const char *target){
  return strcmp(current, target) == 0;
}

// Remove node with given filename
int remove_node(list list, const char *target){
  if (list == NULL)
    return 0;

  node current = list->head;
  node prev = NULL;

  // check if head is target
  if (current != NULL && check_filename(current->filename, target)){
    list->head = current->next;
    destroy_node(current);
    return 1;
  }

  while (current != NULL)
  {
    if (check_filename(current->filename, target)){
      prev->next = current->next;
      destroy_node(current);
      return 1;
    }
    prev = current;
    current = current->next;
  }

  return 0;
}

// Getters
node get_head(list list){
  return list->head;
}

node get_next(node node){
  return node->next;
}

char *get_filename(node node){
  return node->filename;
}
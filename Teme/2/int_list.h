#ifndef __INT_LIST_H
#define __INT_LIST_H
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint8_t data;
  uint8_t *next;
} int_list_node;

typedef struct {
  int_list_node *head;
  int_list_node *tail;
  size_t size;
} int_list;

// Init
void init(int_list *list);
// Add to end
void add_node(int_list *list, uint8_t data);
// Remove from front
void remove_node(int_list *list);
// Get front
uint8_t get_front(int_list *list);
// Get back
uint8_t get_back(int_list *list);
// Get size
size_t get_size(int_list *list);
// Add two lists
int_list add_lists(int_list *list1, int_list *list2);
// Free list
void free_list(int_list *list);

#endif

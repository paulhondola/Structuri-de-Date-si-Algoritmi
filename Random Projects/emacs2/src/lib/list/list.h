// Basic operations on a list of files
#ifndef __LIST_H
#define __LIST_H

// Constants
#define MAX_FILE_NAME_SIZE 128
#define MAX_FILE_CONTENT_SIZE 8192

// Structures
typedef struct NODE *node;
typedef struct LIST *list;

// Constructor
list init_list(void);

// Destructor
void destroy_node(node);
void destroy_list(list);

// Add a node to the back of the list
int add_node(list, const char*);

// Remove a node from the list with the given filename
int remove_node(list, const char*);

// Getters
node get_head(list);
node get_next(node);
char *get_filename(node);

#endif

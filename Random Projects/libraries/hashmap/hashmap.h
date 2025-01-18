//
// Created by Paul Hondola on 21.11.2024.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>

typedef struct HASHMAP *hashmap;

// Constructor
hashmap hashmap_create();

// Destructor
void hashmap_destroy(hashmap map);

// Insert a key-value pair
void hashmap_insert(hashmap map, int key, int value);

// Search for the existence of a key
int hashmap_contains(hashmap map, int key);

// Find first value with given key
int hashmap_find(hashmap map, int key);

// Remove
void hashmap_remove(hashmap map, int key);

// Debugging
void hashmap_print(hashmap map, FILE *file);

#endif //HASHMAP_H

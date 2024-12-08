//
// Created by Paul Hondola on 21.11.2024.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>

#define MAX_HASHMAP_SIZE 100
#define MAX_TITLE_LENGTH 100
#define MAX_GENRE_LENGTH 50
#define MAX_AWARDS_LENGTH 3

typedef struct
{
    int year;
    int length;
    char title[MAX_TITLE_LENGTH];
    char genre[MAX_GENRE_LENGTH];
    char awards[MAX_AWARDS_LENGTH];
} movie;

typedef struct HASHMAP *hashmap;

// Constructor
hashmap hashmap_create();

// Destructor
void hashmap_destroy(hashmap map);

// Insert a key-value pair
void hashmap_insert(hashmap map, movie *mov);

// Search for the existence of a key
int hashmap_contains(hashmap map, char *key);

// Find first value with given key
movie hashmap_find(hashmap map, char *key);

// Remove
void hashmap_remove(hashmap map, char *key);

// Debugging
void hashmap_print(hashmap map, FILE *file);

#endif //HASHMAP_H

//
// Created by Paul Hondola on 21.11.2024.
//
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

// Typedefs
typedef struct BUCKET *bucket;
typedef struct HASHNODE *hashnode;

// Structs
// an, durata, titlu, gen, premii si un pointer la urm

struct HASHNODE{
    movie movie;
    struct HASHNODE *next;
};

struct BUCKET{
    size_t bucket_size;
    hashnode head;
    hashnode tail;
};

struct HASHMAP{
    size_t hashmap_size;
    bucket *buckets;
};

// Hash
size_t hash(char *key){
    size_t code = 0;
    for(size_t i = 0; key[i] != '\0'; i++){
        code += key[i];
    }
    return code % MAX_HASHMAP_SIZE;
}

// Constructors
hashnode node_create(movie *movie){
    hashnode new_node = malloc(sizeof(struct HASHNODE));
    new_node->movie = *movie;
    new_node->next = NULL;
    return new_node;
}

bucket bucket_create(){
    bucket new_bucket = malloc(sizeof(struct BUCKET));
    new_bucket->bucket_size = 0;
    new_bucket->head = NULL;
    new_bucket->tail = NULL;
    return new_bucket;
}

hashmap hashmap_create(){
    hashmap map = malloc(sizeof(struct HASHMAP));
    map->hashmap_size = 0;
    map->buckets = NULL;
    return map;
}

// Destructors
void node_destroy(hashnode node){
    free(node);
}

void bucket_destroy(bucket bucket){
    hashnode current = bucket->head;
    while(current != NULL){
        hashnode temp = current;
        current = current->next;
        node_destroy(temp);
    }
    free(bucket);
}

void hashmap_destroy(hashmap map){
    // Free all nodes in the list
    for(size_t i = 0; i < map->hashmap_size; i++){
        bucket_destroy(map->buckets[i]);
    }
    // Free the list
    free(map->buckets);
    // Free the hashmap
    free(map);
}

// Insert
void bucket_insert(bucket bucket, hashnode node){
    if(bucket->head == NULL){
        bucket->head = node;
        bucket->tail = node;
    } else {
        bucket->tail->next = node;
        bucket->tail = node;
    }
    bucket->bucket_size++;
}

void hashmap_insert(hashmap map, movie *movie){
    // Compute the index
    size_t index = hash(movie->title);

    // Check for map size
    if(map->hashmap_size <= index){
        // Resize the bucket array
        map->buckets = realloc(map->buckets, (index+1) * sizeof(bucket));
        // Init the buckets
        for(size_t i = map->hashmap_size; i <= index; i++){
            map->buckets[i] = bucket_create();
        }
    }

    // Create the new node and add it to the bucket
    bucket_insert(map->buckets[index], node_create(movie));
    map->hashmap_size = map->hashmap_size > index ? map->hashmap_size : index + 1;
}

// Search
int node_contains(hashnode node, char *key){
    return strcmp(node->movie.title, key) == 0;
}

int bucket_contains(bucket bucket, char *key){
    hashnode current = bucket->head;
    while(current != NULL){
        if(node_contains(current, key))
            return 1;
        current = current->next;
    }
    return 0;
}

int hashmap_contains(hashmap map, char *key){
    size_t index = hash(key);
    if(map->hashmap_size <= index)
        return 0;
    return bucket_contains(map->buckets[index], key);
}

// Find
movie node_find(hashnode node, char *key){
    if(strcmp(node->movie.title, key) == 0)
        return node->movie;
    return (movie){0, 0, "", "", ""};
}

movie bucket_find(bucket bucket, char *key){
    hashnode current = bucket->head;
    while(current != NULL){
        movie current_movie = node_find(current, key);
        if(strcmp(current_movie.title, key) == 0)
            return current_movie;
        current = current->next;
    }
    return (movie){0, 0, "", "", ""};
}

movie hashmap_find(hashmap map, char *key){
    size_t index = hash(key);
    if(map->hashmap_size <= index)
        return (movie){0, 0, "", "", ""};
    return bucket_find(map->buckets[index], key);
}

// Remove
void bucket_remove(bucket bucket, char *key){
    hashnode current = bucket->head;
    hashnode prev = NULL;
    while(current != NULL){
        if(node_contains(current, key)){
            if(prev == NULL){
                bucket->head = current->next;
            } else {
                prev->next = current->next;
            }
            if(current == bucket->tail){
                bucket->tail = prev;
            }
            node_destroy(current);
            bucket->bucket_size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void hashmap_remove(hashmap map, char *key){
    size_t index = hash(key);
    if(map->hashmap_size <= index)
        return;
    bucket_remove(map->buckets[index], key);
}

// Debugging
void node_print(hashnode node, FILE *file){
    fprintf(file, "Year: %d | Length: %d | Title: %s | Genre: %s | Awards: %s\n", node->movie.year, node->movie.length, node->movie.title, node->movie.genre, node->movie.awards);
}

void bucket_print(bucket bucket, FILE *file){
    hashnode current = bucket->head;
    while(current != NULL){
        node_print(current, file);
        current = current->next;
    }
}

void hashmap_print(hashmap map, FILE *file){
    for(size_t i = 0; i < map->hashmap_size; i++){
        if(map->buckets[i]->bucket_size == 0)
            continue;
        fprintf(file, "Bucket %zu\n", i);
        bucket_print(map->buckets[i], file);
    }
}
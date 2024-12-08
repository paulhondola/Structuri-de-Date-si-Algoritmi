//
// Created by Paul Hondola on 21.11.2024.
//
#include <stdlib.h>
#include "hashmap.h"
#define MAX_SIZE 100

// Typedefs
typedef struct BUCKET *bucket;
typedef struct HASHNODE *hashnode;

// Structs
struct HASHNODE{
    uint32_t key;
    uint32_t value;
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
size_t hash(int key){
    if(key < 0)
        key *= -1;
    return key % MAX_SIZE;
}

size_t coolhash(size_t key) {
    key ^= key >> 33;
    key *= 0xff51afd7ed558ccd;
    key ^= key >> 33;
    key *= 0xc4ceb9fe1a85ec53;
    key ^= key >> 33;
    return key;
}

// Constructors
hashnode node_create(int key, int value){
    hashnode new_node = malloc(sizeof(struct HASHNODE));
    new_node->key = key;
    new_node->value = value;
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

void hashmap_insert(hashmap map, int key, int value){
    // Compute the index
    size_t index = hash(key);

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
    bucket_insert(map->buckets[index], node_create(key, value));
    map->hashmap_size = map->hashmap_size > index ? map->hashmap_size : index + 1;
}

// Search
int node_contains(hashnode node, int key){
    return node->key == key;
}

int bucket_contains(bucket bucket, int key){
    hashnode current = bucket->head;
    while(current != NULL){
        if(node_contains(current, key))
            return 1;
        current = current->next;
    }
    return 0;
}

int hashmap_contains(hashmap map, int key){
    size_t index = hash(key);
    if(map->hashmap_size <= index)
        return 0;
    return bucket_contains(map->buckets[index], key);
}

// Find
int node_find(hashnode node, int key){
    if(node->key == key)
        return node->value;
    return -1;
}

int bucket_find(bucket bucket, int key){
    hashnode current = bucket->head;
    while(current != NULL){
        int value = node_find(current, key);
        if(value != -1)
            return value;
        current = current->next;
    }
    return -1;
}

int hashmap_find(hashmap map, int key){
    size_t index = hash(key);
    if(map->hashmap_size <= index)
        return -1;
    return bucket_find(map->buckets[index], key);
}

// Remove
void bucket_remove(bucket bucket, int key){
    hashnode current = bucket->head;
    hashnode prev = NULL;
    while(current != NULL){
        if(current->key == key){
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

void hashmap_remove(hashmap map, int key){
    size_t index = hash(key);
    if(map->hashmap_size <= index)
        return;
    bucket_remove(map->buckets[index], key);
}

// Debugging
void node_print(hashnode node, FILE *file){
    fprintf(file, "Key: %d, Value: %d\n", node->key, node->value);
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
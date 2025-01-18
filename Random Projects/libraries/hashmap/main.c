#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hashmap.h"

void random_insert(hashmap map, int n){
    for(int i = 0; i < n; i++){
        int key = rand() % 1000;
        int value = rand() % 1000;
        printf("Inserting key: %d, value: %d\n", key, value);
        hashmap_insert(map, key, value);
    }
}

int main(void)
{
    srand(time(NULL));

    hashmap map = hashmap_create();

    random_insert(map, 100);

    hashmap_insert(map, 5, 69696969);
    hashmap_insert(map, 5, 69696969);
    hashmap_insert(map, 5, 69696969);
    hashmap_insert(map, 205, 69696969);

    hashmap_print(map, stdout);

    printf("----- REMOVING -----\n");

    hashmap_remove(map, 5);
    hashmap_remove(map, 5);

    hashmap_print(map, stdout);

    hashmap_destroy(map);

    return 0;
}

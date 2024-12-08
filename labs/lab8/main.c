#include <stdio.h>
#include "hashmap.h"

void print_movie(movie *mov, FILE *file){
    if(mov->year == 0)
        fprintf(file, "Movie not found\n");
    else
        fprintf(file, "Year: %d | Length: %d | Title: %s | Genre: %s | Awards: %s\n", mov->year, mov->length, mov->title, mov->genre, mov->awards);
}

int main(void)
{
    FILE *f = fopen("Filme.txt", "r");

    if(f == NULL)
        return 1;

    hashmap map = hashmap_create();
    movie mov;
    int i = 0;

    while(fscanf(f, "%d %d %[^\t] %[^\t] %[^\t\n\r] ", &mov.year, &mov.length, mov.title, mov.genre, mov.awards) == 5){
        hashmap_insert(map, &mov);
        i++;
    }

    hashmap_print(map, stdout);

    printf("------ Search for Movies ------\n");
    mov = hashmap_find(map, "Roma");
    print_movie(&mov, stdout);

    mov = hashmap_find(map, "The Favourite");
    print_movie(&mov, stdout);

    hashmap_destroy(map);

    printf("Movies read: %d\n", i);
    return 0;
}

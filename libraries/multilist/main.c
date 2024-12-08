#include "multilist.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct DATA
{
    int key;
    char value[11];
} *data;

data init_data(int key, char *value){
    data d = malloc(sizeof(data));
    d->key = key;
    strcpy(d->value, value);
    return d;
}

void print_data(void * d, FILE *file){
    data aux = d;
    fprintf(file, "%d: %s", aux->key, aux->value);
}


char get_random_char(){
    return 'a' + rand() % 26;
}

data generate_data(){
    data d = malloc(sizeof(data));
    d->key = rand() % 100;
    for (int i = 0; i < 10; i++){
        d->value[i] = get_random_char();
    }
    d->value[10] = '\0';

    return d;
}

node generate_node(){
    data d = generate_data();
    return init_node(d);
}

list generate_list(int size){
    list l = init_list();
    for (int i = 0; i < size; i++){
        node n = generate_node();
        add_node_to_list_back(l, n);
    }
    return l;
}

multilist generate_multilist(int size, int list_size){
    multilist ml = init_multilist();
    for (int i = 0; i < size; i++){
        list l = generate_list(list_size);
        add_list_to_multilist_back(ml, l);
    }
    return ml;
}

int main(void)
{
    srand(time(NULL));
    FILE *log = fopen("log.txt", "w");
    if (log == NULL)
    {
        perror("Error opening log file");
        return 1;
    }

    multilist ml = generate_multilist(10, 5);

    print_multilist(ml, log, print_data);

    destroy_multilist(ml);

    fclose(log);

    return 0;
}
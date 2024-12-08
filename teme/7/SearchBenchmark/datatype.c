#include "datatype.h"

struct DATATYPE{
    unsigned key;
};

data_t get_datatype(const unsigned key) {
    data_t data = malloc(sizeof(struct DATATYPE));
    data->key = key;
    return data;
}

unsigned get_key(const data_t data) {
    return data->key;
}

void print_datatype(const data_t data, FILE *file) {
    fprintf(file, "Key: %u\n", data->key);
}

void free_datatype(const data_t data) {
    free(data);
}
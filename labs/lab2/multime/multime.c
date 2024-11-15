#include "multime.h"
#include <stdbool.h>
#include <string.h>

struct SET {
  char name[MAX_NAME_LENGTH];
  bool *hash_table;
  size_t max_value;
  size_t size;
  size_t sum;
  float average;
};

set init(char *name, size_t size, size_t max_value) {

  // edge case
  if (size > max_value)
    return NULL;

  // allocate memory for the set and initialize it
  set my_set = malloc(sizeof(struct SET));
  *my_set = (struct SET){.name = "",
                         .hash_table = NULL,
                         .max_value = max_value,
                         .size = size,
                         .sum = 0,
                         .average = 0};

  // allocate memory for the hash table
  my_set->hash_table = calloc(my_set->max_value, sizeof(bool));

  // set the name
  // strcpy_s(my_set->name, MAX_NAME_LENGTH, name); -> only for Windows
  strncpy(my_set->name, name, MAX_NAME_LENGTH); // -> for Unix

  // generate random values and add them to the set, compute the sum
  for (size_t i = 0; i < my_set->size; i++) {
    size_t random_value = rand() % my_set->max_value;

    if (my_set->hash_table[random_value]) {
      i--;
      continue;
    }

    my_set->hash_table[random_value] = true;
    my_set->sum += random_value;
  }

  // compute the average
  my_set->average = (float)my_set->sum / my_set->size;

  // return the set
  return my_set;
}

set get_intersection(set set1, set set2, FILE *file) {

  size_t max_intersect_value =
      (set1->max_value > set2->max_value) ? set1->max_value : set2->max_value;
  set intersect = malloc(sizeof(struct SET));
  *intersect =
      (struct SET){.name = "intersecton",
                   .hash_table = calloc(max_intersect_value, sizeof(bool)),

                   .max_value = max_intersect_value,
                   .size = 0,
                   .sum = 0,
                   .average = 0};

  for (size_t i = 0; i < intersect->max_value; i++)
    if (set1->hash_table[i] && set2->hash_table[i])
      intersect->hash_table[i] = true;

  for (size_t i = 0; i < intersect->max_value; i++)
    if (intersect->hash_table[i]) {
      intersect->size++;
      intersect->sum += i;
    }

  intersect->average = (float)intersect->sum / intersect->size;

  return intersect;
}

void show_elements(set my_set, FILE *file) {
  for (size_t i = 0; i < my_set->max_value; i++)
    if (my_set->hash_table[i])
      fprintf(file, "%zu ", i);
  fprintf(file, "\n");
}

void show_data(set my_set, FILE *file) {
  fprintf(file, "Name: %s\n", my_set->name);
  fprintf(file, "Size: %zu\n", my_set->size);
  fprintf(file, "Max Value: %zu\n", my_set->max_value);
  fprintf(file, "Sum: %zu\n", my_set->sum);
  fprintf(file, "Average: %f\n", my_set->average);
}

int *get_biggest2(set my_set) {
  int *biggest2 = malloc(2 * sizeof(int));

  // init
  biggest2[0] = -1;
  biggest2[1] = -1;

  for (size_t i = my_set->max_value - 1; i > 0; i--) {
    if (my_set->hash_table[i]) {
      if (biggest2[0] == -1)
        biggest2[0] = i;
      else if (biggest2[1] == -1)
        biggest2[1] = i;
      else
        break;
    }
  }

  return biggest2;
}

void destroy(set my_set) {
  free(my_set->hash_table);
  free(my_set);
}

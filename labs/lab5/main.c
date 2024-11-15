#include "../../libraries/quicksort.h"
#include "../../libraries/timer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// citire fisier -> filme, coloana numar de vizionari
// sortare dupa timpul de rulare (sortare stabila)
// dupa, sortare dupa numele filmului
// sortat descrescator dupa timp, crescator dupa nume
// in situ

#define MAX_MOVIE_COUNT 2000
#define MAX_MOVIE_TITLE_LENGTH 200
#define MAX_LINE_LENGTH 500
#define MAX_GENRE_LENGTH 50

typedef struct {
  size_t release_year;
  size_t duration;
  char title[MAX_MOVIE_TITLE_LENGTH];
  char genre[MAX_GENRE_LENGTH];
  size_t views;
} movie_t;

int compare_runtime_desc_title_asc(const void *p, const void *q) {
  movie_t a = *(movie_t *)p;
  movie_t b = *(movie_t *)q;

  size_t runtime_a = a.duration * a.views;
  size_t runtime_b = b.duration * b.views;

  if (runtime_a != runtime_b)
    return runtime_b - runtime_a;

  return strcmp(a.title, b.title);
}

void read_movies(movie_t movies[], size_t *size, FILE *file) {
  // consume the header
  char line[MAX_LINE_LENGTH];
  fgets(line, MAX_LINE_LENGTH, file);
  printf("%s", line);

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    movie_t movie;

    // tokenize the line
    char *token = strtok(line, "\t");

    // release year
    movie.release_year = atoi(token);
    token = strtok(NULL, "\t");

    // views
    movie.views = atoi(token);
    token = strtok(NULL, "\t");

    // duration
    movie.duration = atoi(token);
    token = strtok(NULL, "\t");

    // title
    strncpy(movie.title, token, MAX_MOVIE_TITLE_LENGTH - 1);
    token = strtok(NULL, "\t");

    // genre
    strncpy(movie.genre, token, MAX_GENRE_LENGTH - 1);
    token = strtok(NULL, "\t");

    // awards
    token = strtok(NULL, "\t");

    movies[(*size)++] = movie;
  }
}

void print_movies(movie_t *movies, size_t size, FILE *file) {
  for (size_t i = 0; i < size; i++) {
    fprintf(file, "%zu %zu %zu %s %s \n", movies[i].release_year,
            movies[i].duration, movies[i].views, movies[i].title,
            movies[i].genre);
  }
}

int main(void) {

  movie_t movies[MAX_MOVIE_COUNT];
  size_t size = 0;

  FILE *input = fopen("Filme_vizionari.txt", "r");
  if (input == NULL) {
    perror("Could not open file");
    return 1;
  }

  FILE *output = fopen("Filme_sortate.txt", "w");

  read_movies(movies, &size, input);

  print_movies(movies, size, stdout);

  quicksort(movies, size, sizeof(movies[0]), compare_runtime_desc_title_asc);

  print_movies(movies, size, output);

  fclose(input);
  fclose(output);

  return 0;
}

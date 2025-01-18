#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINES 5
#define COLUMNS 5

int matrix[LINES][COLUMNS] = {0};
int visited[LINES][COLUMNS] = {0};

typedef struct {
  int x;
  int y;
} point;

// N S E W
point directions[] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
#define DIRECTIONS 4
int found_exit = 0;

void print_matrix(int matrix[LINES][COLUMNS]) {
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      printf("%2d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int is_downhill(point old, point new) {
  return matrix[old.x][old.y] > matrix[new.x][new.y];
}

int valid(point p) {
  return p.x >= 0 && p.x < LINES && p.y >= 0 && p.y < COLUMNS;
}

int is_visited(point p) { return visited[p.x][p.y]; }

int is_exit(point p) {
  return p.x == 0 || p.y == 0 || p.x == LINES - 1 || p.y == LINES - 1;
}

void back(point p) {
  if (is_exit(p)) {
    found_exit++;
    printf("Exit found at: %2d %2d\n", p.x, p.y);
    print_matrix(visited);
    return;
  }

  point next;

  for (int i = 0; i < DIRECTIONS; i++) {
    next.x = p.x + directions[i].x;
    next.y = p.y + directions[i].y;

    if (is_downhill(p, next) && valid(next) && !is_visited(next)) {
      visited[next.x][next.y] = visited[p.x][p.y] + 1;
      back(next);
      visited[next.x][next.y] = 0;
    }
  }
}

void generate_random_matrix() {
  for (int i = 0; i < LINES; i++)
    for (int j = 0; j < COLUMNS; j++)
      matrix[i][j] = rand() % 20;
}

int main() {
  srand(time(NULL));

  point start = {rand() % LINES, rand() % COLUMNS};
  printf("Starting position: %2d %2d\n", start.x, start.y);
  visited[start.x][start.y] = 1;

  generate_random_matrix();
  print_matrix(matrix);
  back(start);

  printf("Exits found: %d\n", found_exit);

  return 0;
}

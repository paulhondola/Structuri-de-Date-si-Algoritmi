#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6
#define M 6
int matrix[N][M];
int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void generate_matrix() {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      if (rand() % 10 < 4)
        matrix[i][j] = 1;
      else
        matrix[i][j] = 0;
}

void print_matrix() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int is_inside(int x, int y) { return x >= 0 && x < N && y >= 0 && y < M; }
int is_valid(int x, int y) { return is_inside(x, y) && matrix[x][y] == 1; }

void floodfill_sector(int x, int y) {
  for (int i = 0; i < 4; i++) {
    int new_x = x + directions[i][0];
    int new_y = y + directions[i][1];
    if (is_valid(new_x, new_y)) {
      matrix[new_x][new_y] = matrix[x][y] + 1;
      floodfill_sector(new_x, new_y);
    }
  }
}

int floodfill() {
  int sectors = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      if (matrix[i][j] == 1) {
        sectors++;
        matrix[i][j] = 2;
        floodfill_sector(i, j);
      }

  return sectors;
}

int main() {
  srand(time(NULL));
  generate_matrix();
  print_matrix();
  int sectors = floodfill();

  printf("\nSectors: %d\n\n", sectors);
  print_matrix();

  return 0;
}

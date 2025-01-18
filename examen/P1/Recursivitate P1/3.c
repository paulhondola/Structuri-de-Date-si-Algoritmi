#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

#define COLOR_COUNT 4
#define LINES 5
#define COLUMNS 5

typedef struct {
  int x;
  int y;
} point;

point diagonals[] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

typedef enum { WHITE, RED, GREEN, YELLOW, BLUE } color;
color matrix[LINES][COLUMNS] = {WHITE};

void print_color(color c) {
  switch (c) {
  case WHITE:
    printf(COLOR_RESET "W ");
    break;
  case RED:
    printf(COLOR_RED "R ");
    break;
  case GREEN:
    printf(COLOR_GREEN "G ");
    break;
  case YELLOW:
    printf(COLOR_YELLOW "Y ");
    break;
  case BLUE:
    printf(COLOR_BLUE "B ");
    break;
  }
}

void print_matrix() {
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      print_color(matrix[i][j]);
    }
    printf(COLOR_RESET "\n");
  }
}

int is_valid_next(int x, int y) {
  return x >= 0 && x < LINES && y >= 0 && y < COLUMNS;
}

int is_valid_color(int x, int y, color c) {
  for (int i = 0; i < 4; i++) {
    int dx = x + diagonals[i].x;
    int dy = y + diagonals[i].y;
    if (is_valid_next(dx, dy) && matrix[dx][dy] == c) {
      return 0; // Same color on the diagonal
    }
  }
  return 1;
}

int backtracking(int x, int y) {
  if (x == LINES) {
    return 1; // Completed filling the matrix
  }

  int next_x = (y + 1 == COLUMNS) ? x + 1 : x;
  int next_y = (y + 1 == COLUMNS) ? 0 : y + 1;

  for (int c = 1; c <= COLOR_COUNT; c++) {
    if (is_valid_color(x, y, c)) {
      matrix[x][y] = c; // Assign color
      if (backtracking(next_x, next_y)) {
        return 1;
      }
      matrix[x][y] = WHITE; // Backtrack
    }
  }
  return 0; // No valid color found
}

int main(void) {
  srand(time(NULL));
  printf("Initial Matrix:\n");
  print_matrix();

  if (backtracking(0, 0)) {
    printf("\nFilled Matrix:\n");
    print_matrix();
  } else {
    printf("No valid solution exists.\n");
  }

  return 0;
}

#include <stdio.h>

#define LINES 3
#define COLUMNS 3

int matrix[LINES][COLUMNS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

void print_matrix(int matrix[LINES][COLUMNS]) {
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {}

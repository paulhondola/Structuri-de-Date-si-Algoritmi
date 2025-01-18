#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 6
#define M 6
#define INITIAL_BATTERY 2
int maze[N][M];
int visited[N][M] = {0};
int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int found_exits = 0;

void print(int matrix[N][M]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      printf("%2d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int is_inside(int x, int y) { return x >= 0 && x < N && y >= 0 && y < M; }

int is_exit(int x, int y) {
  return x == 0 || x == N - 1 || y == 0 || y == M - 1;
}

int is_wall(int x, int y) { return maze[x][y] == -1; }

int is_visited(int x, int y) { return visited[x][y]; }

int is_valid(int x, int y, int battery) {
  return is_inside(x, y) && !is_wall(x, y) && !is_visited(x, y) && battery > 0;
}

void back(int x, int y, int battery) {
  if (is_exit(x, y)) {
    found_exits++;
    printf("Exit found at: %2d %2d\n", x, y);
    print(visited);
    return;
  }

  for (int i = 0; i < 4; i++) {
    int new_x = x + directions[i][0];
    int new_y = y + directions[i][1];

    if (is_valid(new_x, new_y, battery)) {
      visited[new_x][new_y] = visited[x][y] + 1;
      battery += maze[new_x][new_y];

      back(new_x, new_y, battery - 1);

      visited[new_x][new_y] = 0;
      battery -= maze[new_x][new_y];
    }
  }
}

void maze_generator() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      maze[i][j] = 0;
      if (rand() % 10 > 5) {
        maze[i][j] = -1;
      }
      if (rand() % 10 < 2)
        maze[i][j] = rand() % 4 + 1;
    }
  }
}

int main(void) {

  srand(time(NULL));
  maze_generator();

  int start_x = -1, start_y = -1;

  do {
    start_x = rand() % N;
    start_y = rand() % M;
  } while (maze[start_x][start_y] == -1 || is_exit(start_x, start_y));

  printf("Start Position: %d %d\n", start_x, start_y);
  visited[start_x][start_y] = 1;

  printf("Maze:\n");
  print(maze);

  back(start_x, start_y, INITIAL_BATTERY + maze[start_x][start_y]);

  printf("Found exits: %d\n", found_exits);
  return 0;
}

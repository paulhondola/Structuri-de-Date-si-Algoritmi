#include <stdio.h>

// DIRECTIONS CONSTANTS
#define DIRECTIONS 8
const int directions[DIRECTIONS][2] = { {0, 1},{0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

// MAZE CONSTANTS
#define M 4
#define N 5
const int maze[M][N] = { {3, 0, 0, 0, -1}, {4, 5, 9, 2, -1}, {0, 0, -1, 1, -1}, {1, 0, -1, 0, 1} };
int visited[M][N] = { 0 };
int path[M][N] = { 0 };

// MAZE VARIABLES
int start_x = 0;
int start_y = 0;
int end_x = 3;
int end_y = 4;
int resource_counter = 0;
int steps = 0;
int max_resources = 0;
int min_steps = 0;

// CONTROL FUNCTIONS
int is_wall(int x, int y) {
        return maze[x][y] == -1;
}

int is_valid(int x, int y) {
        return x >= 0 && x < M && y >= 0 && y < N;
}

int is_exit(int x, int y) {
        return x == end_x && y == end_y;
}

int is_visited(int x, int y) {
        return visited[x][y];
}

void copy_matrix(int src[M][N], int dest[M][N]) {
        for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                        dest[i][j] = src[i][j];
}

void print_matrix(int matrix[M][N]) {
        printf("--------------------\n");
        for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++)
                        printf("%d ", matrix[i][j]);
                printf("\n");
        }

        printf("--------------------\n");
}

void found_path() {
        // If the resources are greater than the maximum, update the maximum
        if (resource_counter > max_resources) {
                max_resources = resource_counter;
                min_steps = steps;
                copy_matrix(visited, path);
        } else if (resource_counter == max_resources) {
                // If the resources are equal, check if the steps are less
                if (steps < min_steps) {
                        min_steps = steps;
                        copy_matrix(visited, path);
                }
        }
}

// SOLVER FUNCTION
void back(int x, int y) {
        if (is_exit(x, y)) {
                found_path();
                return;
        }

        for (int i = 0; i < DIRECTIONS; i++) {
                int next_x = x + directions[i][0];
                int next_y = y + directions[i][1];

                if (!is_visited(next_x , next_y) && !is_wall(next_x, next_y) && is_valid(next_x, next_y)) {
                        // continue path
                        visited[next_x][next_y] = visited[x][y] + 1;
                        resource_counter += maze[next_x][next_y];
                        steps++;

                        back(next_x, next_y);

                        // reset path
                        visited[next_x][next_y] = 0;
                        resource_counter -= maze[next_x][next_y];
                        steps--;
                }
        }
}

int main(void) {

        visited[start_x][start_y] = 1;
        resource_counter = maze[start_x][start_y];
        back(start_x, start_y);

        print_matrix(maze);
        printf("Max Resources: %d\n" , max_resources);
        printf("Min Steps: %d\n" , min_steps);
        print_matrix(path);

        return 0;
}
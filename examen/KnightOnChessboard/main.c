#include <stdio.h>
#include <stdlib.h>
// CONSTANTS
#define LINES 6
#define COLUMNS 6
int board[LINES][COLUMNS] = {0};

// DIRECTIONS
#define DIRECTIONS 8
int directions[DIRECTIONS][2] = {
        {-2, -1}, {-2, 1}, {-1, 2}, {1, 2},
        {2, -1}, {2, 1}, {-1, -2}, {1, -2}
};

// START VARIABLES
int start_x = 0, start_y = 0;

// PRINT BOARD
void print_board(void) {
        printf("-------------------------------------\n");
        for (int i = 0; i < LINES; i++) {
                for (int j = 0; j < COLUMNS; j++) {
                        printf("%d ", board[i][j]);
                }
                printf("\n");
        }
        printf("-------------------------------------\n");
}

// CONTROL CHECKERS
int is_valid(int x, int y) {
        return x >= 0 && x < LINES && y >= 0 && y < COLUMNS;
}

int is_visited(int x, int y) {
        return board[x][y];
}

int is_solution(int x, int y) {
        return board[x][y] == LINES * COLUMNS;
}

void back(int x, int y) {
        if (is_solution(x, y)) {
                print_board();
                exit(0);
        }

        for (int i = 0; i < DIRECTIONS; i++) {
                int next_x = x + directions[i][0];
                int next_y = y + directions[i][1];

                printf("X: %d, Y: %d\n", next_x, next_y);
                if (is_valid(next_x, next_y) && !is_visited(next_x, next_y)) {
                        board[next_x][next_y] = board[x][y] + 1;
                        back(next_x, next_y);
                        board[next_x][next_y] = 0;
                }
        }
}

int main(void) {

        board[start_x][start_y] = 1;
        back(start_x, start_y);

        return 0;
}
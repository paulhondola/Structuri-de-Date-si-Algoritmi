#include <stdio.h>

// labyrinth problem
#define MAX_SIZE_X 10
#define MAX_SIZE_Y 10
#define DIRECTIONS 4

int found_exit = 0;

typedef struct POINT {
        int x;
        int y;
} point;

const point directions[DIRECTIONS] = {
        {0, 1}, // down
        {1, 0}, // right
        {0, -1}, // up
        {-1, 0} // left
};

int labyrinth[MAX_SIZE_X][MAX_SIZE_Y] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int is_valid_point(const point p) {
        return p.x >= 0 && p.x < MAX_SIZE_X && p.y >= 0 && p.y < MAX_SIZE_Y;
}

int is_wall(const point p) {
        return labyrinth[p.x][p.y] == 1;
}

int is_visited(const point p) {
        return labyrinth[p.x][p.y] != 0;
}

int is_exit(const point p) {
        return !is_wall(p) && (p.x == 0 || p.x == MAX_SIZE_X - 1 || p.y == 0 || p.y == MAX_SIZE_Y - 1);
}

void print_labyrinth(void) {
        for (int i = 0; i < MAX_SIZE_X; i++) {
                for (int j = 0; j < MAX_SIZE_Y; j++) {
                        printf("%2d ", labyrinth[i][j]);
                }
                printf("\n");
        }
        printf("---------------------------\n");
}

void backtrack(point p) {

        if (found_exit) return;

        for (int i = 0; i < DIRECTIONS; i++) {
                point next = {p.x + directions[i].x, p.y + directions[i].y};

                if (is_exit(next)) {
                        labyrinth[next.x][next.y] = labyrinth[p.x][p.y] + 1;
                        printf("Exit found at (%d, %d)\n", next.x, next.y);
                        print_labyrinth();
                        found_exit = 1; // Marchează căutarea ca fiind completă
                        return;
                }

                if (is_valid_point(next) && !is_wall(next) && !is_visited(next)) {
                        labyrinth[next.x][next.y] = labyrinth[p.x][p.y] + 1;
                        print_labyrinth();
                        backtrack(next);
                        if (found_exit) return; // Verifică dacă căutarea a fost oprită
                }
        }
}

int main(void) {
        point start = {5, 5};
        labyrinth[start.x][start.y] = 2;
        backtrack(start);

        if (!found_exit) {
                printf("No exit found.\n");
        }

        return 0;
}
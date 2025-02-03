#include <stdio.h>
#include <stdlib.h>

int is_valid(int stack[], int level) {
        for (int i = 0; i < level; i++)
                if (abs(i - level) == abs(stack[i] - stack[level]) || stack[i] == stack[level])
                        return 0;
        return 1;
}

int is_solution(int level, int max) {
        return level == max - 1;
}

void print(int stack[], int max) {
        for (int i = 0; i < max; i++) {
                for (int j = 0; j < max; j++) {
                        if (stack[i] == j)
                                printf("Q ");
                        else
                                printf(". ");
                }
                printf("\n");
        }
        printf("----------------\n");
}

void back(int stack[], int level, int max) {
        for (int i = 0; i < max; i++) {
                stack[level] = i;
                if (is_valid(stack, level)) {
                        if (is_solution(level, max))
                                print(stack, max);
                        else
                                back(stack, level + 1, max);
                }
        }
}

int main(void) {
        int max = 8;
        int stack[8] = {0};
        int level = 0;
        back(stack, level, max);
        return 0;
}
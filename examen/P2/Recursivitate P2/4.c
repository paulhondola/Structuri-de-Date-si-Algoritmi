#include <stdio.h>

#define DIGIT_COUNT 6
#define ZERO_COUNT 2
#define ONE_COUNT 4
// 11 start 0 end

void print_stack(int stack[DIGIT_COUNT]) {
  for (int i = 0; i < DIGIT_COUNT; i++) {
    printf("%d ", stack[i]);
  }
  printf("\n");
}

int valid(int st[], int level) {
  int digits[2] = {1, 2};

  for (int i = 2; i <= level; i++)
    digits[st[i]]++;

  return digits[0] <= ZERO_COUNT && digits[1] <= ONE_COUNT;
}

int solution(int level) { return level == DIGIT_COUNT - 2; }

void back(int st[], int level) {
  for (int i = 0; i <= 1; i++) {
    st[level] = i;
    if (valid(st, level)) {
      if (solution(level)) {
        print_stack(st);
      } else {
        back(st, level + 1);
      }
    }
  }
}

int main() {

  int stack[DIGIT_COUNT] = {1, 1, 0, 0, 0, 0};
  back(stack, 2);

  return 0;
}

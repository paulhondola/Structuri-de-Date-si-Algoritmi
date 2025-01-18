#include <stdio.h>

#define PHONE_NUMBER_LENGTH 10

void print(int st[]) {
  for (int i = 0; i < PHONE_NUMBER_LENGTH; i++) {
    printf("%d", st[i]);
  }
  printf("\n");
}

int valid(int st[], int k) {
  for (int i = 4; i < PHONE_NUMBER_LENGTH - 1; i++)
    if (st[i] % 2 == 0 && st[i + 1] % 2 == 0)
      return 0;
  return 1;
}

int solutie(int st[], int k) { return k == PHONE_NUMBER_LENGTH - 2; }

void back(int st[], int k) {
  for (int i = 0; i < PHONE_NUMBER_LENGTH; i++) {
    st[k] = i;
    if (valid(st, k)) {
      if (solutie(st, k)) {
        print(st);
      } else {
        back(st, k + 1);
      }
    }
  }
}

int main(void) {
  int st[PHONE_NUMBER_LENGTH] = {0, 7, 9, 9, -1, -1, -1, -1, -1, 0};
  int k = 4;
  back(st, k);
  return 0;
}

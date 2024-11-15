#include "timer.h"
#include <stdio.h>
int main(void) {
  double time = start();

  for (int i = 0; i < 1000000; i++) {
    printf("%d\n", i);
  }

  time = stop();
  printf("time: %f\n", time);
}

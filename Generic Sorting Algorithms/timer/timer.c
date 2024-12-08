#include "timer.h"
#include <time.h>

clock_t aux;

double start(void) {
  aux = clock();
  return 0;
}
double stop(void) { return (clock() - (double)aux) / CLOCKS_PER_SEC; }

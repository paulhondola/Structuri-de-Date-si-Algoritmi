/* fisierul timer.c */
#include "timer.h"
#include <time.h>
clock_t aux;
void starton(void) { aux = clock(); }
float startoff(void) { return (clock() - (float)aux) / CLOCKS_PER_SEC; }

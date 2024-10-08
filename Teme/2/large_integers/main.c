#include "large_integers.h"

int main(void) {

  large_int a = create("-1100000000000000000000000000000000");
  large_int b = create("-99");
  large_int c = add(a, b);

  printf("%d\n", greater(a, b));

  print(c, stdout);

  destroy(a);
  destroy(b);
  destroy(c);
  return 0;
}

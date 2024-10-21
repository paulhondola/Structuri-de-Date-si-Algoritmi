#include <stdint.h>

uint64_t factorial(uint64_t number) {
  uint64_t result = 1;
  for (uint64_t i = 1; i <= number; i++) {
    result *= i;
  }
  return result;
}

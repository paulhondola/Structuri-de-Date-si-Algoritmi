#include "../libraries/swap.h"

void swap_elements(void *a, void *b, size_t element_size) {
  char temp[element_size];
  memcpy(temp, a, element_size);
  memcpy(a, b, element_size);
  memcpy(b, temp, element_size);
}

#include "stack.h"
#include <time.h>

int compare_stack_data(const void *p, const void *q) {
  return *(stack_data *)p - *(stack_data *)q;
}

void insertion_sort(stack input_stack) {
  stack temp = init_stack(get_stack_top(input_stack));
  stack sorted = init_stack(get_stack_top(input_stack));

  // Process each element of the input stack
  while (!stack_is_empty(input_stack)) {
    stack_data current = peek(input_stack);
    pop(input_stack);

    // Move elements from sorted_stack to temp_stack if they
    // are greater than current

    while (!stack_is_empty(sorted)) {

      stack_data aux = peek(sorted);

      if (compare_stack_data(&aux, &current) >= 0)
        break;

      push(temp, peek(sorted));
      pop(sorted);
    }

    // Push the current element into sorted_stack
    push(sorted, current);

    // Move elements back from temp_stack to sorted_stack
    while (!stack_is_empty(temp)) {
      push(sorted, peek(temp));
      pop(temp);
    }
  }

  // Now the sorted_stack holds the sorted elements, transfer them back to the
  // input_stack
  while (!stack_is_empty(sorted)) {
    push(input_stack, peek(sorted));
    pop(sorted);
  }

  free_stack(temp);
  free_stack(sorted);
}

int main(void) {

  srand(time(NULL));
  const size_t size = 100;
  stack s = init_stack(size);

  for (size_t i = 0; i < size; i++) {
    s = push(s, rand() % 100);
  }

  print_stack(s);

  printf("----------------\n");

  insertion_sort(s);

  print_stack(s);

  return 0;
}

#define MAX_SIZE 100000
#include "large_integers.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// TYPES

// sign = 0 -> negative
// sign = 1 -> positive
struct LARGE_INT {
  bool sign;
  uint32_t size;
  uint8_t *digits;
};

// FUNCTIONS

// CREATE
large_int create(char *number) {
  uint32_t len = strlen(number);
  large_int result = malloc(sizeof(struct LARGE_INT));

  result->sign = number[0] == '+';
  result->size = len - 1;
  result->digits = malloc(result->size);

  for (uint32_t i = 0; i < result->size; i++) {
    result->digits[i] = number[result->size - i] - '0';
  }

  return result;
}

// DESTROY
void destroy(large_int number) {
  free(number->digits);
  free(number);
}

// PRINT
void print(large_int number, FILE *file) {

  if (number->sign)
    fprintf(file, "+");
  else
    fprintf(file, "-");

  for (uint32_t i = 0; i < number->size; i++) {
    fprintf(file, "%d", number->digits[number->size - i - 1]);
  }
}

// ADD

// AUX

bool same_sign(large_int a, large_int b) { return a->sign == b->sign; }

bool greater_aux(large_int a, large_int b) {
  if (a->size > b->size)
    return true;
  if (a->size < b->size)
    return false;

  for (uint32_t i = a->size; i > 1; i--) {
    if (a->digits[i - 1] > b->digits[i - 1])
      return true;
    if (a->digits[i - 1] < b->digits[i - 1])
      return false;
  }

  return a->digits[0] > b->digits[0];
}

bool greater(large_int a, large_int b) {

  if (a->sign && !b->sign)
    return true;

  if (!a->sign && b->sign)
    return false;

  bool result = greater_aux(a, b);
  if (a->sign && b->sign)
    return result;
  else
    return !result;
}

large_int add_aux(large_int a, large_int b) {
  large_int result = malloc(sizeof(struct LARGE_INT));

  result->sign = a->sign;
  result->size = a->size > b->size ? a->size : b->size;
  result->digits = malloc(result->size);

  uint8_t carry = 0;
  for (uint32_t i = 0; i < result->size; i++) {
    uint8_t sum = carry;
    sum += a->digits[i] * (i < a->size);
    sum += b->digits[i] * (i < b->size);
    result->digits[i] = sum % 10;
    carry = sum / 10;
  }

  if (carry) {
    result->size++;
    result->digits = realloc(result->digits, result->size);
    result->digits[result->size - 1] = carry;
  }

  return result;
}

large_int sub_aux(large_int a, large_int b) {
  large_int result = malloc(sizeof(struct LARGE_INT));
  return result;
}

large_int add(large_int a, large_int b) {

  if (same_sign(a, b))
    return add_aux(a, b);
  else
    return sub_aux(a, b);
}
// MULTIPLY

// POWER

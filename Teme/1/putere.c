#include <stdio.h>

double power(double base, double exponent) {
  double result = 1;
  for (int i = 0; i < exponent; i++) {
    result *= base;
  }

  return result;
}

int main() {
  double base, exponent;
  printf("Introduceti baza si exponentul: ");
  scanf("%lf %lf", &base, &exponent);

  printf("Rezultatul este: %lf\n", power(base, exponent));

  return 0;
}

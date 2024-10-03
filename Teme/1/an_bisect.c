#include <stdio.h>

double leap_year(int year) {
  if (year % 400 == 0)
    return 1;

  if (year % 100 == 0)
    return 0;

  if (year % 4 == 0)
    return 1;

  return 0;
}

int main() {
  int year;
  printf("Introduceti un an: ");
  scanf("%d", &year);

  if (leap_year(year))
    printf("Anul %d este bisect.\n", year);
  else
    printf("Anul %d nu este bisect.\n", year);

  return 0;
}

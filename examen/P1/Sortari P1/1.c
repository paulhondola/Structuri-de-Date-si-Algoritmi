/*
Fie un tablou de elemente care a căror valori sunt numere întregi, pozitive sau
negative. Sã se aleagă si sã se modifice unul din algoritmii de sortare
studiati, astfel incât:
- valorile negative vor fi aduse la începutul tabloului (rezultatul va fi un
tablou cu toate elementele negative la început, si toate elementele pozitive la
sfârsit)
- valorile pozitive vor fi sortate crescător
Algoritmul modificat trebuie sa fie cât mai eficient.
Motivati alegerea algoritmului.
Exemplificati functionearea algoritmului pe un tablou de 6 elemente.
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int cmp(const void *p, const void *q) { return (*(int *)p - *(int *)q); }

void sort(int numbers[], int count) {
  int neg_index = 0;

  // O(n) pentru a muta toate numerele negative la inceput
  for (int i = 0; i < count; i++) {
    if (numbers[i] < 0) {
      swap(&numbers[i], &numbers[neg_index++]);
    }
  }

  // O(nlogn) pentru a sorta numerele pozitive
  qsort(numbers + neg_index, count - neg_index, sizeof(*numbers), cmp);
}

int main() {

  int numbers[] = {9, -4, 3, -2, 5, -6, 7, -8, 1, -10};
  int numbers_count = sizeof(numbers) / sizeof(numbers[0]);

  sort(numbers, numbers_count);

  for (int i = 0; i < numbers_count; i++) {
    printf("%d ", numbers[i]);
  }

  return 0;
}

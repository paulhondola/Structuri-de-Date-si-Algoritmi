/*
Fie un tablou de structuri de forma struct angajat{char nume(35]; int salar; int
bonus). (Câmpul bonus este setat pe 1 dacă angajatul a primit un bonus,
respectiv pe 0 daca nu). Stiind ca tabloul are dimensiunea N, sa se implementeze
cate o functie pentru:
a. Mutarea, intr-un mod cat mai eficient, pe primele
pozitii din vector a angajatilor care au primit bonus,
b. Sortarea in ordine
inversa dupa salar, a angajatilor care NU au primit bonus (doar acesti angajati
vor fi sortati).
Sa se considere un exemplu de tablou cu minim 5 astfel de
angajati si sa se exemplifice cum va arata tabloul dupa apelul fiecareia din
functiile de mai sus.
*/
#include <stdio.h>

#define NAME_LEN 35

typedef struct {
  char name[NAME_LEN];
  int salary;
  int bonus;
} employee;

int salary_condition(employee *a, employee *b) { return a->salary > b->salary; }

void swap(employee *a, employee *b) {
  employee tmp = *a;
  *a = *b;
  *b = tmp;
}

void sort_bonus_first(employee e[], int size) {
  int index = 0;
  // O(n) complexity
  // binsort like implementation
  for (int i = 0; i < size; i++)
    if (e[i].bonus)
      swap(&e[i], &e[index++]);
}

int bonus_count(employee e[], int size) {
  int count = 0;
  for (int i = 0; i < size; i++)
    if (e[i].bonus)
      count++;
  return count;
}

// O(nlogn) complexity
void quicksort(employee a[], int prim, int ultim,
               int (*condition)(employee *, employee *)) {
  int stanga = prim + 1;
  int dreapta = ultim;
  // alegere pivot
  swap(&a[prim], &a[(prim + ultim) / 2]);
  // mutare pivot pe prima pozitie
  employee pivot = a[prim];

  while (stanga <= dreapta)
  // partitionare
  {
    while (condition(&a[stanga], &pivot))
      stanga++;
    while (condition(&pivot, &a[dreapta]))
      dreapta--;
    if (stanga < dreapta)
      swap(&a[stanga++], &a[dreapta--]);
    else
      stanga++;
  }
  // mutare pivot la locul sau final
  swap(&a[dreapta], &a[prim]);
  // apelurile recursive
  if (prim < dreapta - 1)
    quicksort(a, prim, dreapta - 1, condition);
  if (dreapta + 1 < ultim)
    quicksort(a, dreapta + 1, ultim, condition);
}

void print_employee(employee *e) {
  printf("Name: %s |", e->name);
  printf("Salary: %d |", e->salary);
  printf("Bonus: %d", e->bonus);
}

void print_arr(employee e[], int size) {
  for (int i = 0; i < size; i++) {
    print_employee(&e[i]);
    printf("\n");
  }
}

int main(void) {

  employee employees[] = {{"Paul", 1000, 0},
                          {"Ion", 3000, 0},
                          {"Maria", 4000, 1},
                          {"Ana", 5000, 0},
                          {"George", 2000, 1}};

  int size = sizeof(employees) / sizeof(employees[0]);

  printf("Before sorting:\n");
  print_arr(employees, size);

  printf("---------------------------------\n");
  printf("Bonus first:\n");
  sort_bonus_first(employees, size);
  print_arr(employees, size);

  printf("---------------------------------\n");
  printf("Descending after salary without bonus:\n");
  quicksort(employees, bonus_count(employees, size), size, salary_condition);
  print_arr(employees, size);

  return 0;
}

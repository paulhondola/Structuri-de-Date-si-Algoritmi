/*
Se dau urmatoarele 6 culori: alb, galben, rosu, verde, albastru si negru.
Sa se implementeze structurile de date necesare si urmatoarele functionalitati:
• Construiti toate steagurile formate din 3 culori care indeplinesc urmatoarele
conditii:

• orice steag trebuie sa contina culoarea verde sau culoarea galben la
mijloc.
• culorile din fiecare steag trebuie sa fie distincte.

Sa se aleaga cel putin 3 exemple de steaguri si sa se reprezinte grafic.
Descrieti continutul structurilor de date folosite dupa apelul functiilor
corespunzatoare.
*/

#include <stdio.h>

#define FLAG_COUNT NEGRU
#define MAX_FLAGS 3
typedef enum { ALB = 1, GALBEN, ROSU, VERDE, ALBASTRU, NEGRU } culori;

int valid(int st[], int k) {
  for (int i = 1; i < k; i++)
    for (int j = i + 1; j <= k; j++)
      if (st[i] == st[j])
        return 0;

  if (k > 1 && (st[2] != VERDE && st[2] != GALBEN))
    return 0;

  return 1;
}

int solutie(int k) { return k == MAX_FLAGS; }

void afiseaza(int st[], int k) {
  for (int i = 1; i <= k; i++) {
    switch (st[i]) {
    case ALB:
      printf("ALB ");
      break;

    case GALBEN:
      printf("GALBEN ");
      break;

    case ROSU:
      printf("ROSU ");
      break;

    case VERDE:
      printf("VERDE ");
      break;

    case ALBASTRU:
      printf("ALBASTRU ");
      break;

    case NEGRU:
      printf("NEGRU ");
      break;
    }
  }
  printf("\n");
}

void back(int st[], int k) {
  for (int i = 1; i <= FLAG_COUNT; i++) {
    st[k] = i;
    if (valid(st, k)) {
      if (solutie(k))
        afiseaza(st, k);
      else
        back(st, k + 1);
    }
  }
}

int main(void) {
  int st[MAX_FLAGS + 1] = {0};
  back(st, 0);
  return 0;
}

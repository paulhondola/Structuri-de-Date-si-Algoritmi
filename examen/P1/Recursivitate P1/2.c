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

#define COD_ALB "\x1b[37m"
#define COD_GALBEN "\x1b[33m"
#define COD_ROSU "\x1b[31m"
#define COD_VERDE "\x1b[32m"
#define COD_ALBASTRU "\x1b[34m"
#define COD_NEGRU "\x1b[30m"
#define RST "\x1b[0m"

#define FLAG_COUNT NEGRU
#define MAX_FLAGS 3
typedef enum { ALB = 1, GALBEN, ROSU, VERDE, ALBASTRU, NEGRU } culori;

int valid(int st[], int k) {
  if (k > 1 && (st[2] != VERDE && st[2] != GALBEN))
    return 0;

  for (int i = 1; i < k; i++)
    for (int j = i + 1; j <= k; j++)
      if (st[i] == st[j])
        return 0;

  return 1;
}

int solutie(int k) { return k == MAX_FLAGS; }

void afiseaza(int st[], int k) {
  for (int i = 1; i <= k; i++) {
    switch (st[i]) {
    case ALB:
      printf(COD_ALB "ALB ");
      break;

    case GALBEN:
      printf(COD_GALBEN "GALBEN ");
      break;

    case ROSU:
      printf(COD_ROSU "ROSU ");
      break;

    case VERDE:
      printf(COD_VERDE "VERDE ");
      break;

    case ALBASTRU:
      printf(COD_ALBASTRU "ALBASTRU ");
      break;

    case NEGRU:
      printf(COD_NEGRU "NEGRU ");
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

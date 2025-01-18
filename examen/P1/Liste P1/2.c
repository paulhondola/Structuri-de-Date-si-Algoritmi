#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUME_LEN 20

typedef struct PRODUS {
  int cod;
  struct PRODUS *next;
} *produs;

typedef struct MAGAZIN {
  char nume[NUME_LEN];
  struct MAGAZIN *next;
  produs produse;
} *magazin;

produs create_produs(int cod) {
  produs p = (produs)malloc(sizeof(struct PRODUS));
  p->cod = cod;
  p->next = NULL;
  return p;
}

produs add_produs(produs p, int cod) {
  produs q = create_produs(cod);
  q->next = p;
  return q;
}

magazin create_magazin(char nume[], produs p) {
  magazin m = (magazin)malloc(sizeof(struct MAGAZIN));
  strncpy(m->nume, nume, NUME_LEN);
  m->next = NULL;
  m->produse = p;
  return m;
}

magazin add_magazin(magazin m, char nume[], produs p) {
  magazin q = create_magazin(nume, p);
  q->next = m;
  return q;
}

void print_produs(produs p) {
  while (p) {
    printf("%d ", p->cod);
    p = p->next;
  }
}

void print_magazin(magazin m) {
  while (m) {
    printf("%s: ", m->nume);
    print_produs(m->produse);
    printf("\n|\n");
    m = m->next;
  }
}

produs sterge_produse(produs p, int cod) {
  // sterge din cap
  while (p && p->cod == cod) {
    produs temp = p;
    p = p->next;
    free(temp);
  }

  // daca lista e goala
  if (!p)
    return NULL;

  produs q = p;
  // sterge din interior
  while (q && q->next) {
    if (q->next->cod == cod) {
      produs temp = q->next;
      q->next = q->next->next;
      free(temp);
    } else {
      q = q->next;
    }
  }

  return p;
}

magazin sterge_din_magazin(magazin m, int cod) {
  magazin q = m;
  while (q) {
    q->produse = sterge_produse(q->produse, cod);
    q = q->next;
  }

  return m;
}

int main(void) {

  srand(time(NULL));
  produs p[5] = {NULL};
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      p[i] = add_produs(p[i], rand() % 10);

  magazin m = NULL;
  for (int i = 0; i < 5; i++) {
    char nume[20];
    sprintf(nume, "Magazin %d", i);
    m = add_magazin(m, nume, p[i]);
  }

  print_magazin(m);
  printf("----------------------------------\nDupa stergere:\n");
  m = sterge_din_magazin(m, 5);
  print_magazin(m);

  return 0;
}

/*
Fie un sistem de gestionare a unor paleti din cadrul unor depozite. Depozitul
este caracterizat printr-un nume unic, iar paletii printr-un cod numeric (max 8
cifre). Sa se scrie si sa se implementeze o structura multilista adecvata pentru
gestionarea acestor depozite. Structura va avea urmatoarea componenta: Fiecare
depozit reprezinta o intrare separata intr-o lista principala, si fiecare
depozit contine o lista secundara ordonata dupa cod a paletilor din acel zbor
(cel putin una din liste va fi implementata dinamic). Sa se implementeze
structurile de date necesare si urmatoarele functionalitati: •Eliminare palet-
se sterge un palet identificat dupa cod din toate depozitele. Sa se aleaga un
exemplu de lista care sa cuprinda cel putin 3 depozite, fiecare cu cel putin 5
paleti. Sa se reprezinte grafic structura multilista pentru acest exemplu,
inainte si dupa apelul functiei Eliminare palet.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NAME_LEN 20
#define H 5
#define V 5

typedef struct PALET {
  int cod;
  struct PALET *next;
} *palet;

typedef struct DEPOZIT {
  char nume[NAME_LEN];
  struct DEPOZIT *next;
  palet paleti;
} *depozit;

void print_palet(palet p) {
  while (p) {
    printf("%d ", p->cod);
    p = p->next;
  }
}

void print_depozit(depozit d) {
  while (d) {
    printf("%s: ", d->nume);
    print_palet(d->paleti);
    printf("\n|\n");
    d = d->next;
  }
}

palet create_palet(int cod) {
  palet p = (palet)malloc(sizeof(struct PALET));
  p->cod = cod;
  p->next = NULL;
  return p;
}

void add_palet(palet *p, int cod) {
  palet q = create_palet(cod);
  q->next = *p;
  *p = q;
}

depozit create_depozit(char nume[], palet p) {
  depozit d = (depozit)malloc(sizeof(struct DEPOZIT));
  strncpy(d->nume, nume, NAME_LEN);
  d->next = NULL;
  d->paleti = p;
  return d;
}

void add_depozit(depozit *d, char nume[], palet p) {
  depozit q = create_depozit(nume, p);
  q->next = *d;
  *d = q;
}

void generate_random_paleti(palet p[], int palet_horizontal,
                            int palet_vertical) {
  for (int i = 0; i < palet_horizontal; i++)
    p[i] = create_palet(rand() % 10);

  for (int i = 0; i < palet_horizontal; i++)
    for (int j = 0; j < palet_vertical; j++)
      add_palet(&p[i], rand() % 10);
}

void erase_from_palet(palet *p, int cod) {
  // erase from head
  while (p && (*p)->cod == cod) {
    palet temp = *p;
    *p = (*p)->next;
    free(temp);
  }

  // erase from middle or tail
  palet q = *p;
  while (q && q->next) {
    if (q->next->cod == cod) {
      palet temp = q->next;
      q->next = q->next->next;
      free(temp);
    } else
      q = q->next;
  }
}

void erase_from_depozit(depozit *d, int cod) {
  depozit q = *d;
  while (q) {
    erase_from_palet(&q->paleti, cod);
    q = q->next;
  }
}

int main(void) {
  srand(time(NULL));
  palet p[H];
  generate_random_paleti(p, H, V);

  depozit d = NULL;
  add_depozit(&d, "d1", p[0]);
  add_depozit(&d, "d2", p[1]);
  add_depozit(&d, "d3", p[2]);
  add_depozit(&d, "d4", p[3]);
  add_depozit(&d, "d5", p[4]);

  print_depozit(d);

  printf("------------------------------------------\nAfter removal:\n");

  erase_from_depozit(&d, 0);
  print_depozit(d);

  return 0;
}

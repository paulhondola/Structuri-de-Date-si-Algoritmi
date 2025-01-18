#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUME_FIRMA_LEN 20
#define COD_GPS_LEN 9
#define CAMIOANE_PER_FIRMA 5

typedef struct CAMION {
  char cod_gps[COD_GPS_LEN];
  struct CAMION *next;
} camion;

typedef struct FIRMA {
  char nume[NUME_FIRMA_LEN];
  struct FIRMA *next;
  int nr_camioane;
  camion camioane[CAMIOANE_PER_FIRMA];
} *firma;

camion creare_camion(char cod_gps[COD_GPS_LEN]) {
  camion c;
  strcpy(c.cod_gps, cod_gps);
  c.next = NULL;
  return c;
}

firma creare_firma(char nume[NUME_FIRMA_LEN]) {
  firma f = (firma)malloc(sizeof(struct FIRMA));
  strcpy(f->nume, nume);
  f->next = NULL;
  f->nr_camioane = 0;
  return f;
}

void adauga_camion(firma f, char cod_gps[COD_GPS_LEN]) {
  if (f->nr_camioane >= CAMIOANE_PER_FIRMA) {
    printf("Nu se mai pot adauga camioane la firma %s\n", f->nume);
    return;
  }

  camion c = creare_camion(cod_gps);

  f->camioane[f->nr_camioane].next = &c;
  f->camioane[f->nr_camioane++] = c;
}

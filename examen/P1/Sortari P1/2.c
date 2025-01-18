/*
Fie un tablou de structuri de forma struct agenda
char nume[25]; char telefon[10];int an; int venit
Stiind ca tabloul are dimensiunea N, sa se implementeze cate o functie pentru:
a. Mutarea pe ultimele pozitii din vector a primelor două persoane cu un venit
mai mic de 1000.
b. Sortarea eficientă, în ordine alfabeticã a numelor, a
persoanelor cu vârsta între 30 si 40 de ani. Sa se considere un exemplu de
tablou cu minim 5 astfel de agende si sa se exemplifice cum va arata tabloul
dupa apelul fiecareia din functiile de mai SUS.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 25
#define PHONE_LEN 10
#define N 10

typedef struct {
  char name[NAME_LEN];
  char phone[PHONE_LEN];
  int year;
  int income;
} phonebook;

int income_condition(phonebook *pb) { return pb->income < 1000; }

int age_condition(phonebook *pb) { return pb->year >= 30 && pb->year <= 40; }

void print_phonebook(phonebook *pb) {
  printf("Name: %s | Phone: %s | Year: %d | Income: %d", pb->name, pb->phone,
         pb->year, pb->income);
}

void print_phonebook_array(phonebook pb[], int size) {
  for (int i = 0; i < size; i++) {
    print_phonebook(&pb[i]);
    printf("\n");
  }
}

void swap(phonebook *pb1, phonebook *pb2) {
  phonebook tmp = *pb1;
  *pb1 = *pb2;
  *pb2 = tmp;
}

void move(phonebook pb[], int size) {
  int count = 0;
  // O(n) pentru a muta primele doua persoane cu venit mai mic de 1000 la
  // sfarsit
  // mergem pana la size - 3 pentru ca ultimele doua persoane vor fi deja
  // puse la loc in vector
  for (int i = 0; i < size - 2; i++) {
    if (income_condition(&pb[i]))
      swap(&pb[i], &pb[size - 1 - count++]);
    if (count == 2)
      break;
  }
}

int cmp(const void *pb1, const void *pb2) {
  return strcmp(((phonebook *)pb1)->name, ((phonebook *)pb2)->name);
}

void sort(phonebook pb[], int size) {
  // O(n) cost al memoriei
  int sort_size = 0;
  int indexes[size];
  phonebook tmp[size];

  // O(n) pentru a pune persoanele cu varsta intre 30 si 40 in tmp
  for (int i = 0; i < size; i++) {
    if (age_condition(&pb[i])) {
      tmp[sort_size] = pb[i];
      indexes[sort_size] = i;
      sort_size++;
    }
  }

  // O(nlogn) pentru sortare
  qsort(tmp, sort_size, sizeof(*tmp), cmp);

  // O(n) pentru a pune inapoi persoanele sortate in vectorul initial
  for (int i = 0; i < sort_size; i++) {
    pb[indexes[i]] = tmp[i];
  }
}

int main(void) {

  phonebook pb1 = {"Paul", "1234567890", 20, 2000};
  phonebook pb2 = {"Ion", "0987654321", 35, 100};
  phonebook pb3 = {"Maria", "1234567890", 40, 500};
  phonebook pb4 = {"Ana", "0987654321", 45, 2000};
  phonebook pb5 = {"George", "1234567890", 37, 1000};
  phonebook pb6 = {"Mihai", "0987654321", 32, 500};
  phonebook pb7 = {"Andrei", "1234567890", 39, 2000};
  phonebook pb8 = {"Cristina", "0987654321", 35, 1000};
  phonebook pb9 = {"Andreea", "1234567890", 31, 500};
  phonebook pb10 = {"Cristian", "0987654321", 33, 2000};

  phonebook pb[N] = {pb1, pb2, pb3, pb4, pb5, pb6, pb7, pb8, pb9, pb10};

  print_phonebook_array(pb, N);
  printf(
      "------------------------------------------------------------------\n");

  move(pb, N);
  print_phonebook_array(pb, N);

  printf(
      "------------------------------------------------------------------\n");

  sort(pb, N);
  print_phonebook_array(pb, N);
}

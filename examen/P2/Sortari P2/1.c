/*
Fie un tablou de structuri de forma struct echipa(char nume[25]; int puncte; int
buget, char oras(25]}. Stiind ca tabloul are dimensiunea N, sa se implementeze
cate o functie pentru:
a. Mutarea pe primele pozitii din vector a echipelor cu
punctaj mai mare decat 45, iar pe ultimele pozitii a celor cu punctaj mal mic
decat 20. Algoritmul va avea o complexitate de O(n), si nu va folosi un alt
tablou auxiliar;
b. Sortarea cat mai eficienta a echipelor cu un buget mai mare
decat 100 000 (celalalte echipe nu vor fi sortate pastrandu-si aceleasi pozitii
in tablou) descrescator in functie de punctaj. Sa se considere un exemplu de
tablou cu minim 5 astfel de echipe si sa se exemplifice cum va arata tabloul
dupa apelul fiecareia din functiile de mai sus.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int N = 10;
const int NAME_LEN = 25;
const int MAX_SCORE_CONDITION = 45;
const int MIN_SCORE_CONDITION = 20;
const int BUDGET_CONDITION = 100000;

typedef struct {
  char name[NAME_LEN];
  int score;
  int budget;
  char city[NAME_LEN];
} team;

int max_score_condition(team t) { return t.score > MAX_SCORE_CONDITION; }

int min_score_condition(team t) { return t.score < MIN_SCORE_CONDITION; }

int budget_condition(team t) { return t.budget > BUDGET_CONDITION; }

void swap(team *a, team *b) {
  team aux = *a;
  *a = *b;
  *b = aux;
}

int cmp_score_desc(const void *p, const void *q) {
  return ((team *)q)->score - ((team *)p)->score;
}

void move(team t[], int size) {
  int left = 0, right = size - 1;

  // move teams with score > 45 to the front
  for (int i = 0; i < size; i++)
    if (max_score_condition(t[i]))
      swap(&t[i], &t[left++]);

  // and teams with score < 20 to the back
  for (int i = left; i < size; i++)
    if (min_score_condition(t[i]))
      swap(&t[i], &t[right--]);

  // sort separately so there is no breaking of the previous conditions
  // O(n) for each sort
}

void quicksort(team t[], int left, int right) {
  int i = left + 1;
  int j = right;

  swap(&t[left], &t[(left + right) / 2]);

  team pivot = t[left];

  while (i <= j) {
    while (t[i].score < pivot.score)
      i++;
    while (t[j].score > pivot.score)
      j--;
    if (i < j)
      swap(&t[i++], &t[j--]);
    else
      i++;
  }

  swap(&t[j], &t[left]);

  if (left < j - 1)
    quicksort(t, left, j - 1);
  if (j + 1 < right)
    quicksort(t, j + 1, right);
}

void sort(team t[], int size) {
  int indexes[size];
  team tmp[size];
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (budget_condition(t[i])) {
      indexes[count] = i;
      tmp[count] = t[i];
      count++;
    }
  }

  quicksort(tmp, 0, count - 1);

  for (int i = 0; i < count; i++) {
    t[indexes[i]] = tmp[i];
  }
}

void print_team(team *t) {
  printf("Name: %s | ", t->name);
  printf("Score: %2d | ", t->score);
  printf("Budget: %6d | ", t->budget);
  printf("City: %s", t->city);
}

void print_team_arr(team t[], int size) {
  for (int i = 0; i < size; i++) {
    print_team(&t[i]);
    printf("\n");
  }
}

int main(void) {
  srand(time(NULL));
  char team_name[N] = "team_";
  char city_name[N] = "city_";
  team teams[N];

  for (int i = 0; i < N; i++) {
    // concat team_name and city_name with i

    sprintf(teams[i].name, "%s%d", team_name, i);
    sprintf(teams[i].city, "%s%d", city_name, i);

    teams[i].score = (rand() % 10 + 1) * 5;
    teams[i].budget = (rand() % 1000 + 1) * 1000;
  }

  printf("Initial array:\n");
  print_team_arr(teams, N);
  printf("---------------------------------------------------------");

  move(teams, N);
  printf("\nArray after move:\n");
  print_team_arr(teams, N);
  printf("---------------------------------------------------------");

  sort(teams, N);
  printf("\nArray after sort:\n");
  print_team_arr(teams, N);
  return 0;
}

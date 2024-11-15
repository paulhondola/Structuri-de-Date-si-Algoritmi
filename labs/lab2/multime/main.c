#include "multime.h"

int main() {

  // init random seed
  srand(time(NULL));
  // Date
  // elemente intregi (max 10000)
  // marimea
  // numele (max 200)
  // media aritmetica cu virgula

  // Functii
  // init(n, p) valori random pana la p [0, p)
  // afisare_intersectie(multime1, multime2)
  // cele mai mari 2 nr. din multimes

  set my_set = init("test", 20, 100);
  set my_set2 = init("test2", 20, 100);

  show_data(my_set, stdout);
  show_elements(my_set, stdout);

  show_data(my_set2, stdout);
  show_elements(my_set2, stdout);

  set intersect = get_intersection(my_set, my_set2, stdout);

  show_data(intersect, stdout);
  show_elements(intersect, stdout);

  int *biggest2_1 = get_biggest2(my_set);
  int *biggest2_2 = get_biggest2(my_set2);
  int *biggest2_3 = get_biggest2(intersect);

  printf("Biggest 2: %d %d\n", biggest2_1[0], biggest2_1[1]);
  printf("Biggest 2: %d %d\n", biggest2_2[0], biggest2_2[1]);
  printf("Biggest 2: %d %d\n", biggest2_3[0], biggest2_3[1]);

  destroy(my_set);
  destroy(my_set2);
  destroy(intersect);
  free(biggest2_1);
  free(biggest2_2);
  free(biggest2_3);

  return 0;
}

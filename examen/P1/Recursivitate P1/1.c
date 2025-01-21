/*
Se dã multimea M=(a,b,c)
Sa se implementeze structurile de date necesare si urmatoarele functionalitati:
• Generează cuvinte - functia determină toate cuvintele ce contin numai literele
din multimea M de lungime 10 care contin exact 3 simboluri 'a', 4 simboluri 'b'
si 3 simboluri 'c. • Sa se noteze primele 5 cuvinte generate în ordine.
*/

#include <stdio.h>

const char SET[] = {'a', 'b', 'c'};

void generate_words(char *word, int index, int a, int b, int c) {
  if (index == 10) {
    if (a == 3 && b == 4 && c == 3) {
      printf("%s\n", word);
    }
    return;
  }

  for (int i = 0; i < 3; i++) {
    word[index] = SET[i];
    if (SET[i] == 'a') {
      generate_words(word, index + 1, a + 1, b, c);
    } else if (SET[i] == 'b') {
      generate_words(word, index + 1, a, b + 1, c);
    } else {
      generate_words(word, index + 1, a, b, c + 1);
    }
  }
}

#define MAX_LEVEL A_CNT + B_CNT + C_CNT
#define A_CNT 3
#define B_CNT 4
#define C_CNT 3
#define SET_SIZE 3

int valid(int st[], int k) {
  int a = 0, b = 0, c = 0;
  for (int i = 1; i <= k; i++) {
    if (st[i] == 1) {
      a++;
    } else if (st[i] == 2) {
      b++;
    } else {
      c++;
    }
  }

  return a <= A_CNT && b <= B_CNT && c <= C_CNT;
}

int solutie(int k) { return k == MAX_LEVEL; }

void afiseaza(int st[], int k) {
  for (int i = 1; i <= k; i++) {
    printf("%c ", st[i] + 'A' - 1);
  }
  printf("\n");
}

void back_rec(int st[], int k) {
  for (int i = 1; i <= SET_SIZE; i++) {
    st[k] = i;
    if (valid(st, k)) {
      if (solutie(k))
        afiseaza(st, k);
      else
        back_rec(st, k + 1);
    }
  }
}

int main() {
  char word[11];
  generate_words(word, 0, 0, 0, 0);

  int st[MAX_LEVEL + 1] = {0};
  back_rec(st, 0);
  return 0;
}

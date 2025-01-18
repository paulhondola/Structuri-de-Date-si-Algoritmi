/*
Se dã multimea M=(a,b,c)
Sa se implementeze structurile de date necesare si urmatoarele functionalitati:
• Generează cuvinte - functia determină toate cuvintele ce contin numai literele
din multimea M de lungime 10 care contin exact 3 simboluri 'a', 4 simboluri 'b'
si 3 simboluri 'c. • Sa se noteze primele 5 cuvinte generate în ordine.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void generate_words_backtracking(char *word, int level, int a, int b, int c) {}

int main() {
  char word[11];
  generate_words(word, 0, 0, 0, 0);
  return 0;
}

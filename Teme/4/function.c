#include <stdio.h>

void function(int n) {
  for (int i = n; i >= 1; i -= 3) { // Theta(n / 3)
    for (int j = 1; j < i; j++)     // Theta(n / 3)
      for (int k = 1; k < i; k++)   // Theta(n / 3)
        printf("*");
  } // -> Theta (n / 3) * Theta (n / 3) * Theta (n / 3) = Theta(n^3)
}

int main(void) { return 0; }

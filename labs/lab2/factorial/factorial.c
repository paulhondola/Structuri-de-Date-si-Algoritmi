#include <stdio.h>

int factorial_iterativ(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
}

int factorial_recursiv(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial_recursiv(n - 1);
}

int main()
{
    printf("Iterativ %d\n", factorial_iterativ(3));
    printf("Recursiv %d\n", factorial_recursiv(4));
    return 0;
}
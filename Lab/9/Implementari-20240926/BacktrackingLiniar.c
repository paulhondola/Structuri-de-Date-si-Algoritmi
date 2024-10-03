#include <stdio.h>
#define nmax 10
int a[nmax];  // tablou de maxim nmax elemente
int pos[nmax];  //tabloul de posibilitati
void initializare(int n)
{
    //initializarea posibilitatilor
    int i;
    for (i = 0; i < n; i++)
        pos[i] = i + 1;
}

void afiseaza_solutia(int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int acceptabil(int pos, int k)
{
    //elementele din solutie trebuie sa fie unice
    int i;
    for (i = 0; i < k; i++)
        if (a[i] == pos)
            return 0;
    return 1;
}

int solutie(int k, int n)
{
    return (k == n);  //solutia cuprinde n elemente
}

void permuta(int k, int n)  //k pasul, n -nr de elemente
{
    int i, aux;
    if (solutie(k, n))              //solutie completa (avem n elemente)
        afiseaza_solutia(n);
    else
    {
        for (i = 0; i < n; i++)  // parcurgem pe rand posibilitatile
        {
            aux = pos[i];
            if (acceptabil(aux, k)) {//daca posibilitatea  e acceptabila
                a[k] = pos[i];
                permuta(k + 1, n);   // back1(posibilitate_k+1)
            }
            //sterge_inregistrarea lipseste din aceasta implementare;
        }
    }
}   /*permuta*/

int main(void)
{
    //citire n
    int n;
    scanf("%d", &n);
    initializare(n);
    permuta(0, n);
}
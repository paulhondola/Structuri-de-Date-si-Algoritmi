Aplicații recursivitate

I. Să se scrie un program pentru formatarea unui program C. Programul va ține cont de indentarea corectă a codului, de numărul de spații dintre elemente și de situațiile când ar trebui să se continue pe rând nou.

Programul primește ca parametru de intrare un fișier cod .c, îl procesează și furnizează un nou fisier .c formatat

Exemplu:

Codul următor

if ( n==1 ) { n = 2 * m;

if ( m < 10 )

f( n, m-1 ); else f( n,m-2 );} else n = 3 * m;

va deveni:

if ( n == 1)

{

     n = 2 * m;

     if ( m < 10 )

          f ( n, m-1);

     else f (n, m-2);

}

else n = 3 * m;



II. Un pătrat de dimensiune nXn conține celule negre și albe aranjate într-un anumit tipar. Să se determine numărul de zone albe și numărul de celule albe din fiecare zonă.

Ex:

n n n n n n n n

n a a a n a a n

n a a a n a a n

n n a a n n n n

n n n n n a a n

n n n n n a a n

n a a n n n n n

n n n n n n n n

Raspuns:

4 zone:

C1 =  8 celule albe

C2 =  4 celule albe

C3 =  4 celule albe

C4 =  2  celule albe
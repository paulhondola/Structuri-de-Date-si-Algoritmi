### Operatii cu intregi cu numar mare de cifre

## Tablou care contine cifrele numarului

```c
#define MAX_CAPACITY 1000
typedef struct {
	size_t n;
	uint8_t cifre[MAX_CAPACITY];
} big_int_array;
```

## Lista simplu inlantuita care contine cifrele numarului in ordine inversa

```c
typedef struct {
	uint8_t value;
	uint8_t *next;
} big_int_node;

typedef struct {
	big_int_node *head;
	big_int_node *tail;
} big_int_list;
```

# SUMA

Suma a doua numere intregi cu numar mare de cifre se face pe baza algoritmului de adunare pe coloane.

Pentru implementarea cu liste, se parcurg listele si se aduna fiecare cifra de pe aceeasi pozitie, tinand cont de transportul de la o cifra la alta.

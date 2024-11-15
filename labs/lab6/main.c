#include "timer.h"
#include <stdio.h>
#define MAX_LEN 500

typedef struct {
  float data[MAX_LEN][MAX_LEN];
  float square_sum[MAX_LEN];
} matrix_t;

matrix_t m;

int compare_fast();

float compare_square_sums(const void *p, const void *q) {
  return *(float *)p - *(float *)q;
}

void swap(matrix_t *m, int x, int y, int size) {
  // O(n) -> se schimba 2 linii, element cu element
  float temp[size];
  for (int i = 0; i < size; i++) {
    temp[i] = m->data[x][i];
    m->data[x][i] = m->data[y][i];
    m->data[y][i] = temp[i];
  }

  float temp2 = m->square_sum[x];
  m->square_sum[x] = m->square_sum[y];
  m->square_sum[y] = temp2;
}

// 2 functii sortare

void merge(matrix_t *m, int left, int mid, int right, int cols) {

  // O(nlogn) -> complexitatea merge-ului
  // O(n) -> spatiu auxiliar

  int i = left, j = mid + 1, k = 0;
  matrix_t temp;

  while (i <= mid && j <= right) {
    if (compare_square_sums(&m->square_sum[i], &m->square_sum[j]) > 0) {
      temp.square_sum[k] = m->square_sum[i];
      for (int col = 0; col < cols; col++) {
        temp.data[k][col] = m->data[i][col];
      }
      i++;
    } else {
      temp.square_sum[k] = m->square_sum[j];
      for (int col = 0; col < cols; col++) {
        temp.data[k][col] = m->data[j][col];
      }
      j++;
    }
    k++;
  }

  while (i <= mid) {
    temp.square_sum[k] = m->square_sum[i];
    for (int col = 0; col < cols; col++) {
      temp.data[k][col] = m->data[i][col];
    }
    i++;
    k++;
  }

  while (j <= right) {
    temp.square_sum[k] = m->square_sum[j];
    for (int col = 0; col < cols; col++) {
      temp.data[k][col] = m->data[j][col];
    }
    j++;
    k++;
  }

  for (i = left, k = 0; i <= right; i++, k++) {
    m->square_sum[i] = temp.square_sum[k];
    for (int col = 0; col < cols; col++) {
      m->data[i][col] = temp.data[k][col];
    }
  }
}

// Merge sort function
void merge_sort_helper(matrix_t *m, int left, int right, int cols) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    // Sort the first and second halves
    merge_sort_helper(m, left, mid, cols);
    merge_sort_helper(m, mid + 1, right, cols);

    // Merge the sorted halves
    merge(m, left, mid, right, cols);
  }
}

void merge_sort(matrix_t *m, int rows, int cols) {
  merge_sort_helper(m, 0, rows - 1, cols);
}

void selection_sort(matrix_t *m, int rows, int cols) {
  // O(n^2) -> complexitatea algoritmului de sortare
  // O(n^2) -> comparatii de chei (float - float)
  // O(n) -> operatii de interschimbare (swap - O(n))
  for (int i = 0; i < rows - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < rows; j++) {
      if (compare_square_sums(&m->square_sum[j], &m->square_sum[min_idx]) > 0) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      swap(m, i, min_idx, cols);
    }
  }
}

void read() {
  // O(n^2) -> se citeste matricea din fisier
  FILE *f = fopen("matrix.txt", "r");

  if (f == NULL)
    return;

  for (int i = 0; i < MAX_LEN; i++)
    for (int j = 0; j < MAX_LEN; j++)
      fscanf(f, "%f", &m.data[i][j]);

  fclose(f);
}

void compute_square_sums() {
  // O(n^2) -> se face suma patratelor pe fiecare linie, se stocheaza intr-un
  // tablou
  for (int i = 0; i < MAX_LEN; i++) {
    m.square_sum[i] = 0;
    for (int j = 0; j < MAX_LEN; j++) {
      m.square_sum[i] += m.data[i][j] * m.data[i][j];
    }
  }
}

void print_matrix(int rows, int cols) {
  // O(n^2) -> se afiseaza matricea
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%f ", m.data[i][j]);
    }
    printf("\n");
  }
}

void printsums(int size) {
  // O(n) -> se afiseaza suma patratelor pe fiecare linie
  for (int i = 0; i < size; i++) {
    printf("%f ", m.square_sum[i]);
  }
}

void clone(matrix_t *m, matrix_t *cloned) {
  for (int i = 0; i < MAX_LEN; i++) {
    cloned->square_sum[i] = m->square_sum[i];
    for (int j = 0; j < MAX_LEN; j++) {
      cloned->data[i][j] = m->data[i][j];
    }
  }
}

int main(void) {

  matrix_t aux;
  read();
  compute_square_sums();
  clone(&m, &aux);

  FILE *selection_test = fopen("selection_test.txt", "w");
  FILE *merge_test = fopen("merge_test.txt", "w");
  // print_matrix(MAX_LEN, MAX_LEN);

  // SELECTION SORT TEST
  for (int i = 5; i <= MAX_LEN; i++) {
    clone(&m, &aux);
    double time = start();

    selection_sort(&aux, i, i);

    time = stop();

    fprintf(selection_test, "%d %f\n", i, time);
  }

  // MERGE SORT TEST
  for (int i = 5; i <= MAX_LEN; i++) {
    clone(&m, &aux);
    double time = start();

    merge_sort(&aux, i, i);

    time = stop();

    fprintf(merge_test, "%d %f\n", i, time);
  }

  return 0;
}

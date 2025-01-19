
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int id;
  int start_time;
  int end_time;
} task;

int get_duration(task *t) { return t->end_time - t->start_time; }

void swap(task *a, task *b) {
  task aux = *a;
  *a = *b;
  *b = aux;
}

int cmp_duration(task *a, task *b) { return get_duration(a) < get_duration(b); }

int cmp_start(task *a, task *b) { return a->start_time < b->start_time; }

int cmp_end(task *a, task *b) { return a->end_time < b->end_time; }

void deplasare(task a[], int stanga, int dreapta, int (*cmp)(task *, task *)) {
  int fiu = 2 * stanga + 1;
  while (fiu <= dreapta) {
    // daca al doilea fiu are cheia cea mai mare
    if (fiu < dreapta && cmp(&a[fiu], &a[fiu + 1]))
      fiu++;
    // retinem al doilea fiu
    if (cmp(&a[stanga], &a[fiu])) {
      // schimba parinte cu fiu
      swap(&a[stanga], &a[fiu]); // si deplaseaza in jos
      stanga = fiu;
      fiu = 2 * stanga + 1;
    } else
      fiu = dreapta + 1;
  }
}

void heap_sort(task a[], int n, int (*cmp)(task *, task *)) {
  int i;
  // algoritmul lui Floyd
  for (i = n / 2 - 1; i >= 0; i--) // se creaza ansamblul
    deplasare(a, i, n - 1, cmp);
  // extragerea maximului si refacerea ansamblului
  for (i = n - 1; i >= 1; i--) {
    swap(&a[0], &a[i]);
    // mutare element maxim pe pozitia a[i]
    deplasare(a, 0, i - 1, cmp);
    // se reface proprietatea de ansamblu
  }
}

void generate_tasks(task t[], int size) {
  for (int i = 0; i < size; i++) {
    t[i].id = i;
    t[i].start_time = rand() % 100;
    t[i].end_time = t[i].start_time + rand() % 100;
  }
}

void print_task(task t) {
  printf("ID: %d | Start: %d | End: %d\n", t.id, t.start_time, t.end_time);
}

void print_tasks(task t[], int size) {
  for (int i = 0; i < size; i++) {
    print_task(t[i]);
  }
}

int select_tasks(task tasks[], int count, int allocated_time) {
  int task_count = 0;
  int current_time = 0;
  int prev_task_index = 0;
  // check if the first task is doable

  if (tasks[0].end_time > allocated_time)
    return 0;

  // add the first task
  task_count++;
  current_time = tasks[0].end_time;
  prev_task_index = 0;
  printf("Tasks in execution: %d", tasks[0].id);

  for (int i = 1; i < count; i++)
    if (tasks[prev_task_index].end_time < tasks[i].start_time &&
        current_time + get_duration(&tasks[i]) <= allocated_time) {
      task_count++;
      current_time = tasks[i].end_time;
      prev_task_index = i;
      printf(" %d", tasks[i].id);
    }

  return task_count;
}

int main(void) {

  srand(time(NULL));

  const int TASK_COUNT = 10;
  const int ALLOCATED_TIME = 1000;

  task tasks[TASK_COUNT];

  generate_tasks(tasks, TASK_COUNT);
  print_tasks(tasks, TASK_COUNT);
  heap_sort(tasks, TASK_COUNT, cmp_start);
  heap_sort(tasks, TASK_COUNT, cmp_duration);
  printf("\n");
  print_tasks(tasks, TASK_COUNT);
  int count = select_tasks(tasks, TASK_COUNT, ALLOCATED_TIME);
  printf("\nTasks finished: %d\n", count);

  return 0;
}

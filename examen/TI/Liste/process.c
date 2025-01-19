#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRIORITY 9

typedef struct {
  int id;
  int priority;
  int activation_time;
} process;

typedef struct NODE {
  process data;
  struct NODE *next;
} *node;

// queue functions
typedef struct {
  node front;
  node rear;
} queue;

queue init_queue() { return (queue){NULL, NULL}; }

void enqueue(queue *q, node n) {
  if (q->front == NULL) {
    q->front = n;
    q->rear = n;
  } else {
    q->rear->next = n;
    q->rear = n;
  }
}

node dequeue(queue *q) {
  if (q->front == NULL)
    return NULL;

  node n = q->front;
  q->front = q->front->next;
  return n;
}

int is_empty(queue q) { return q.front == NULL; }

void print_process(process p) {
  printf("ID: %d | ", p.id);
  printf("Priority: %d | ", p.priority);
  printf("Activation time: %d\n", p.activation_time);
}

// recursive function to print the list
void print_list(node head) {
  if (head == NULL)
    return;

  print_process(head->data);
  print_list(head->next);
}

void print_multilist(node multilist[]) {
  for (int i = 1; i < MAX_PRIORITY; i++) {
    printf("Priority %d:\n", i);
    print_list(multilist[i]);
    printf("\n");
  }
}

void print_queue(queue q) {
  node current = q.front;
  while (current != NULL) {
    print_process(current->data);
    current = current->next;
  }
}

// generate random process
process generate_process() {
  process p;
  p.id = rand() % 1000;
  p.priority = rand() % 8 + 1;
  p.activation_time = rand() % 100;
  return p;
}

// insert a process in the list, lower activation time is higher priority
void priority_insert(node *head, process p) {
  node new_node = (node)malloc(sizeof(struct NODE));
  new_node->data = p;
  new_node->next = NULL;

  if (*head == NULL) {
    *head = new_node;
    return;
  }

  node current = *head;
  node prev = NULL;

  while (current != NULL && current->data.activation_time < p.activation_time) {
    prev = current;
    current = current->next;
  }

  if (prev == NULL) {
    new_node->next = *head;
    *head = new_node;
  } else {
    prev->next = new_node;
    new_node->next = current;
  }
}

// insert into the multilist structure
void insert_process(node multilist[], process p) {
  priority_insert(&multilist[p.priority], p);
}

// add into the queue the process that has the highest priority and the lowest
// activation time
void add_to_queue(node multilist[], queue *q) {
  for (int i = MAX_PRIORITY - 1; i > 0; i--) {
    if (multilist[i] != NULL) {
      node aux = multilist[i];
      multilist[i] = multilist[i]->next;
      aux->next = NULL;
      enqueue(q, aux);
      return;
    }
  }
}

int main(void) {

  srand(time(NULL));
  node multilist[MAX_PRIORITY] = {NULL};

  for (int i = 0; i < 10; i++) {
    process p = generate_process();
    insert_process(multilist, p);
  }

  print_multilist(multilist);

  queue q = init_queue();

  add_to_queue(multilist, &q);
  add_to_queue(multilist, &q);
  add_to_queue(multilist, &q);

  printf("\nQueue:\n");
  print_queue(q);

  printf("\n\nUpdated multilist:\n");
  print_multilist(multilist);

  return 0;
}

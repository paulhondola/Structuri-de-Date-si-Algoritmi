#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
  int data;
  struct NODE *next;
} *node;

node create_node(int data) {
  node new_node = (node)malloc(sizeof(struct NODE));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

node add_node(node head, int data) {
  node new_node = create_node(data);

  if (head == NULL) {
    return new_node;
  }

  new_node->next = head;
  return new_node;
}

void print_list(node head) {
  node current = head;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

node erase_middle(node head) {
  node prev = head;
  node tortoise = head;
  node hare = head;

  while (hare) {
    hare = hare->next;
    if (hare) {
      hare = hare->next;
    }
    if (hare) {
      prev = tortoise;
      tortoise = tortoise->next;
    }
  }

  node to_delete = prev->next;
  prev->next = prev->next->next;
  free(to_delete);
  return head;
}

int main() {
  node head = NULL;
  head = add_node(head, 1);
  head = add_node(head, 2);
  head = add_node(head, 3);
  head = add_node(head, 4);
  head = add_node(head, 5);
  head = add_node(head, 6);
  head = add_node(head, 7);
  print_list(head);
  head = erase_middle(head);
  print_list(head);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CONNECTIONS 1024
#define MAX_NAME_LEN 35

typedef struct USER {
  int id;
  char name[MAX_NAME_LEN];
  char occupation[MAX_NAME_LEN];
  struct USER *next;

  int nr_connections;
  struct USER *connections[MAX_CONNECTIONS];
} *user;

typedef struct NETWORK {
  user users;
} network;

user create_user(int id, char name[MAX_NAME_LEN],
                 char occupation[MAX_NAME_LEN]) {
  user u = (user)malloc(sizeof(struct USER));
  u->id = id;
  strcpy(u->name, name);
  strcpy(u->occupation, occupation);
  u->next = NULL;
  u->nr_connections = 0;
  return u;
}

void add_user(network *n, user u) {
  u->next = n->users;
  n->users = u;
}

void add_connection(user u1, user u2) {
  if (u1->nr_connections >= MAX_CONNECTIONS) {
    printf("User %s has too many connections\n", u1->name);
    return;
  }

  // check for duplicate connections
  for (int i = 0; i < u1->nr_connections; i++) {
    if (u1->connections[i] == u2) {
      printf("User %s is already connected to %s\n", u1->name, u2->name);
      return;
    }
  }

  u1->connections[u1->nr_connections++] = u2;
}

void print_user(user u) {
  printf("User %s (%s) has %d connections: ", u->name, u->occupation,
         u->nr_connections);

  for (int i = 0; i < u->nr_connections; i++) {
    printf("%s, ", u->connections[i]->name);
  }
}

void print_network(network n) {
  user u = n.users;
  while (u != NULL) {
    print_user(u);
    printf("\n");
    u = u->next;
  }
}

int main(void) {
  user u1 = create_user(1, "John Doe", "Software Engineer");
  user u2 = create_user(2, "Jane Doe", "Data Scientist");
  user u3 = create_user(3, "Alice", "Product Manager");
  user u4 = create_user(4, "Bob", "Software Engineer");
  user u5 = create_user(5, "Charlie", "Data Scientist");
  user u6 = create_user(6, "David", "Product Manager");
  user u7 = create_user(7, "Eve", "Software Engineer");
  user u8 = create_user(8, "Frank", "Data Scientist");
  user u9 = create_user(9, "Grace", "Product Manager");
  user u10 = create_user(10, "Heidi", "Software Engineer");

  user users[10] = {u1, u2, u3, u4, u5, u6, u7, u8, u9, u10};

  srand(time(NULL));

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 4; j++) {
      add_connection(users[i], users[rand() % 10]);
    }
  }

  network n;

  for (int i = 0; i < 10; i++) {
    add_user(&n, users[i]);
  }

  print_network(n);
}

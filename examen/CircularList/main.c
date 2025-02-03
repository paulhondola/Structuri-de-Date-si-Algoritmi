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

void add(node *head, int data) {
        if (*head == NULL) {
                *head = create_node(data);
                return;
        }

        node new = create_node(data);
        new->next = *head;
        *head = new;
}

void print_list(node head) {
        node current = head;
        while (current != NULL) {
                printf("%d -> ", current->data);
                current = current->next;
        }
        printf("\n");
}

int is_circular(node head) {
        node slow = head;
        node fast = head;

        do {
                if (slow == NULL || fast == NULL || fast->next == NULL)
                        return 0;

                slow = slow->next;
                fast = fast->next->next;
        } while (slow != fast);

        return 1;
}

int main(void) {
        node head = NULL;
        add(&head, 1);
        add(&head, 2);
        add(&head, 3);
        add(&head, 4);
        add(&head, 5);

        node tail = head->next->next->next->next;

        tail->next = head;

        printf("Is circular: %d\n", is_circular(head));

        return 0;
}
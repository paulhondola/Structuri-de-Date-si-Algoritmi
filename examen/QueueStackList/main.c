#include <stdio.h>
#include <stdlib.h>
// data structures
typedef struct NODE {
        int data;
        struct NODE *next;
} *node;

typedef struct STACK {
        node top;
} *stack;

typedef struct QUEUE {
        stack data;
        stack aux;
} *queue;

// Stack functions
stack create_stack() {
        return malloc(sizeof(struct STACK));
}

void push(stack stack, int data) {
        node new_node = malloc(sizeof(struct NODE));
        new_node->data = data;
        new_node->next = stack->top;
        stack->top = new_node;
}

node pop(stack stack) {
        if (stack->top == NULL)
                return NULL;

        node top = stack->top;
        stack->top = stack->top->next;
        return top;
}

int stack_empty(stack stack) {
        return stack->top == NULL;
}

void print_stack(stack stack) {
        node current = stack->top;
        while (current != NULL) {
                printf("%d -> ", current->data);
                current = current->next;
        }
        printf("\n");
}

// Queue functions

queue create_queue() {
        queue q = malloc(sizeof(struct QUEUE));
        q->data = create_stack();
        q->aux = create_stack();
        return q;
}

int queue_empty(queue q) {
        return stack_empty(q->data);
}

node dequeue(queue q) {
        // pop from the data stack
        return pop(q->data);
}

void enqueue(queue q, int data) {
        // pop all from the data stack to the aux stack
        // push the new element to the data stack
        // push all from the aux stack to the data stack

        // 1
        while (!stack_empty(q->data))
                push(q->aux, pop(q->data)->data);
        // 2
        push(q->data, data);
        // 3
        while (!stack_empty(q->aux))
                push(q->data, pop(q->aux)->data);
}

void print_queue(queue q) {
        print_stack(q->data);
}

int main(void) {

        queue q = create_queue();
        node tmp = NULL;
        enqueue(q, 1);
        enqueue(q, 2);
        enqueue(q, 3);
        tmp = dequeue(q);
        if (tmp != NULL)
                printf("Dequeued: %d\n", tmp->data);
        enqueue(q, 4);
        tmp = dequeue(q);
        if (tmp != NULL)
                printf("Dequeued: %d\n", tmp->data);
        print_queue(q);

        return 0;
}
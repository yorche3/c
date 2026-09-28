#ifndef DATA_STRUCTURES_BASICS_H
#define DATA_STRUCTURES_BASICS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t count;
} LinkedList;

typedef struct {
    Node *top;
    size_t count;
} Stack;

typedef struct {
    Node *front;
    Node *rear;
    size_t count;
} Queue;

void node_init(Node *node, int value);
int node_get_value(const Node *node);
Node *node_get_next(const Node *node);
void node_set_next(Node *node, Node *next);

void linked_list_init(LinkedList *list);
bool linked_list_is_empty(const LinkedList *list);
size_t linked_list_size(const LinkedList *list);
int linked_list_get_head(const LinkedList *list);
/*
 * Nodo cabeza de la lista, para recorrerla con `node_get_value` y `node_get_next`.
 * Devuelve NULL si la lista está vacía. La especificación pide que el recorrido se
 * observe con operaciones del contrato, sin leer los campos de `LinkedList`.
 */
Node *linked_list_get_head_node(const LinkedList *list);
void linked_list_insert_head(LinkedList *list, int value);
void linked_list_insert_tail(LinkedList *list, int value);
int linked_list_delete(LinkedList *list, int value);

void stack_init(Stack *stack);
bool stack_is_empty(const Stack *stack);
size_t stack_size(const Stack *stack);
void stack_push(Stack *stack, int value);
int stack_pop(Stack *stack);
int stack_peek(const Stack *stack);

void queue_init(Queue *queue);
bool queue_is_empty(const Queue *queue);
size_t queue_size(const Queue *queue);
void queue_enqueue(Queue *queue, int value);
int queue_dequeue(Queue *queue);
int queue_peek(const Queue *queue);

#endif /* DATA_STRUCTURES_BASICS_H */

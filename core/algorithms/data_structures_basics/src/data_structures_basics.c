#include "data_structures_basics.h"

#include <stdlib.h>

/**
 * @def FAILURE_VALUE Valor de retorno que indica fallo en las operaciones con nodos.
 */
#define FAILURE_VALUE (-1)

/**
 * @brief Inicializa un nodo con el valor dado.
 * @param node Puntero al nodo a inicializar.
 * @param value Valor a asignar al nodo.
 */
void node_init(Node *node, int value) {
  if (node != NULL) {
    node->value = value;
    node->next = NULL;
  }
}

/**
 * @brief Obtiene el valor de un nodo.
 * @param node Puntero al nodo.
 * @return Valor del nodo o FAILURE_VALUE si el nodo es NULL.
 */
int node_get_value(const Node *node) {
  if (node != NULL) {
    return node->value;
  }
  return FAILURE_VALUE;
}

/**
 * @brief Obtiene el siguiente nodo de un nodo dado.
 * @param node Puntero al nodo.
 * @return Puntero al siguiente nodo o NULL si el nodo es NULL o no tiene siguiente.
 */
Node *node_get_next(const Node *node) {
  if (node != NULL) {
    return node->next;
  }
  return NULL;
}

/**
 * @brief Asigna el siguiente nodo a un nodo dado.
 * @param node Puntero al nodo.
 * @param next Puntero al siguiente nodo.
 */
void node_set_next(Node *node, Node *next) {
  if (node != NULL) {
    node->next = next;
  }
}

/**
 * @brief Inicializa una lista enlazada.
 * @param list Puntero a la lista enlazada a inicializar.
 */
void linked_list_init(LinkedList *list) {
  if (list != NULL) {
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
  }
}


/**
 * @brief Verifica si una lista enlazada está vacía.
 * @param list Puntero a la lista enlazada.
 * @return true si la lista está vacía, false en caso contrario.
 */
bool linked_list_is_empty(const LinkedList *list) {
  return (list == NULL || list->count == 0);
}

/**
 * @brief Obtiene el tamaño de la lista enlazada.
 * @param list Puntero a la lista enlazada.
 * @return Número de elementos en la lista.
 */
size_t linked_list_size(const LinkedList *list) {
  return (list != NULL) ? list->count : 0;
}

/**
 * @brief Obtiene el valor del nodo cabeza de la lista.
 * @param list Puntero a la lista enlazada.
 * @return Valor del nodo cabeza o FAILURE_VALUE si la lista está vacía o el puntero es NULL.
 */
int linked_list_get_head(const LinkedList *list) {
  if (list != NULL && list->head != NULL) {
    return list->head->value;
  }
  return FAILURE_VALUE;
}

/**
 * @brief Obtiene el nodo cabeza de la lista, para recorrerla con node_get_value/node_get_next.
 * @param list Puntero a la lista enlazada.
 * @return Nodo cabeza o NULL si la lista está vacía o el puntero es NULL.
 */
Node *linked_list_get_head_node(const LinkedList *list) {
  if (list != NULL) {
    return list->head;
  }
  return NULL;
}

void linked_list_insert_head(LinkedList *list, int value) {
  if (list != NULL) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL) {
      new_node->value = value;
      new_node->next = list->head;
      list->head = new_node;
      if (list->tail == NULL) {
        list->tail = new_node;
      }
      list->count++;
    }
  }
}

void linked_list_insert_tail(LinkedList *list, int value) {
  if (list != NULL) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL) {
      new_node->value = value;
      new_node->next = NULL;
      if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
      } else {
        list->tail->next = new_node;
        list->tail = new_node;
      }
      list->count++;
    }
  }
}

/**
 * @brief Elimina la primera aparición de un valor en la lista enlazada.
 * @param list Puntero a la lista enlazada.
 * @param value Valor a eliminar.
 * @return 0 si se eliminó con éxito, FAILURE_VALUE (-1) si el valor no se encuentra.
 */
int linked_list_delete(LinkedList *list, int value) {
  if (list == NULL || list->head == NULL) {
    return FAILURE_VALUE;
  }
  Node *current = list->head;
  Node *previous = NULL;
  while (current != NULL) {
    if (current->value == value) {
      if (previous == NULL) {
        list->head = current->next;
      } else {
        previous->next = current->next;
      }
      free(current);
      list->count--;
      return 0;
    }
    previous = current;
    current = current->next;
  }
  return FAILURE_VALUE;
}

/**
 * @brief Inicializa una pila.
 * @param stack Puntero a la pila a inicializar.
 */
void stack_init(Stack *stack) {
  if (stack != NULL) {
    stack->top = NULL;
    stack->count = 0;
  }
}

/**
 * @brief Verifica si una pila está vacía.
 * @param stack Puntero a la pila.
 * @return true si la pila está vacía, false en caso contrario.
 */
bool stack_is_empty(const Stack *stack) {
  if (stack == NULL || stack->top == NULL) {
    return true;
  }
  return false;
}

/**
 * @brief Obtiene el tamaño de la pila.
 * @param stack Puntero a la pila.
 * @return Número de elementos en la pila.
 */
size_t stack_size(const Stack *stack) {
  if (stack == NULL) {
    return 0;
  }
  return stack->count;
}

/**
 * @brief Inserta un valor en la pila.
 * @param stack Puntero a la pila.
 * @param value Valor a insertar.
 */
void stack_push(Stack *stack, int value) {
  if (stack != NULL) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL) {
      new_node->value = value;
      new_node->next = stack->top;
      stack->top = new_node;
      stack->count++;
    }
  }
}

/**
 * @brief Elimina y retorna el valor superior de la pila.
 * @param stack Puntero a la pila.
 * @return Valor superior de la pila o FAILURE_VALUE si la pila está vacía.
 */
int stack_pop(Stack *stack) {
  if (stack == NULL || stack->top == NULL) {
    return FAILURE_VALUE;
  }
  Node *top_node = stack->top;
  int value = top_node->value;
  stack->top = top_node->next;
  free(top_node);
  stack->count--;
  return value;
}

/**
 * @brief Obtiene el valor superior de la pila sin eliminarlo.
 * @param stack Puntero a la pila.
 * @return Valor superior de la pila o FAILURE_VALUE si la pila está vacía.
 */
int stack_peek(const Stack *stack) {
  if (stack == NULL || stack->top == NULL) {
    return FAILURE_VALUE;
  }
  return stack->top->value;
}

/**
 * @brief Inicializa una cola.
 * @param queue Puntero a la cola a inicializar.
 */
void queue_init(Queue *queue) {
  if (queue != NULL) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
  }
}

/**
 * @brief Verifica si una cola está vacía.
 * @param queue Puntero a la cola.
 * @return true si la cola está vacía, false en caso contrario.
 */
bool queue_is_empty(const Queue *queue) {
  if (queue == NULL || queue->front == NULL) {
    return true;
  }
  return false;
}

/**
 * @brief Obtiene el tamaño de la cola.
 * @param queue Puntero a la cola.
 * @return Número de elementos en la cola.
 */
size_t queue_size(const Queue *queue) {
  if (queue == NULL) {
    return 0;
  }
  return queue->count;
}

/**
 * @brief Inserta un valor en la cola.
 * @param queue Puntero a la cola.
 * @param value Valor a insertar.
 */
void queue_enqueue(Queue *queue, int value) {
  if (queue != NULL) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL) {
      new_node->value = value;
      new_node->next = NULL;
      if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
      } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
      }
      queue->count++;
    }
  }
}

/**
 * @brief Obtiene el valor frontal de la cola sin eliminarlo.
 * @param queue Puntero a la cola.
 * @return Valor frontal de la cola o FAILURE_VALUE si la cola está vacía.
 */
int queue_peek(const Queue *queue) {
  if (queue == NULL || queue->front == NULL) {
    return FAILURE_VALUE;
  }
  return queue->front->value;
}

/**
 * @brief Elimina y retorna el valor frontal de la cola.
 * @param queue Puntero a la cola.
 * @return Valor frontal de la cola o FAILURE_VALUE si la cola está vacía.
 */
int queue_dequeue(Queue *queue) {
  if (queue == NULL || queue->front == NULL) {
    return FAILURE_VALUE;
  }
  Node *front_node = queue->front;
  int value = front_node->value;
  queue->front = front_node->next;
  if (queue->front == NULL) {
    queue->rear = NULL;
  }
  free(front_node);
  queue->count--;
  return value;
}
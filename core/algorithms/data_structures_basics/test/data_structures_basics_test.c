/*
 * Suite de pruebas — data_structures_basics (C)
 * Framework: Criterion
 * Indicador de fallo: FAILURE_VALUE = -1 (entero); ausencia de enlace = NULL (puntero).
 * Adaptaciones de tipo:
 *   - El tipo de secuencia es el struct Node con puntero next (nativo de C).
 *   - La ausencia de enlace usa NULL, representación nativa de C para punteros.
 *   - Los recorridos observan la lista a través de linked_list_get_head_node /
 *     node_get_value / node_get_next, sin acceder a campos internos de LinkedList.
 *   - linked_list_delete devuelve 0 en éxito y -1 en fallo (FAILURE_VALUE).
 * Los casos son pasos sucesivos sobre el mismo estado lógico por estructura,
 * tal como indica la especificación (no se reinicia el escenario entre filas).
 */

#include <criterion/criterion.h>
#include "../include/data_structures_basics.h"

/* --- Helper compartido: recorre la lista desde su cabeza y rellena out[]. ---
 * Retorna el número de elementos encontrados.
 * Usa solo operaciones del contrato, no campos de LinkedList directamente.   */
static int traverse_list(const LinkedList *list, int out[], int max) {
    int count = 0;
    Node *current = linked_list_get_head_node(list);
    while (current != NULL && count < max) {
        out[count++] = node_get_value(current);
        current       = node_get_next(current);
    }
    return count;
}

/* =========================================================================
 * Node — 2 casos (pasos sucesivos sobre los mismos nodos a y b)
 * ========================================================================= */

Test(data_structures_basics, node_should_init_and_observe_value_and_link) {
    /* Caso 1: Inicializar y observar valor/enlace */
    Node a;
    node_init(&a, 10);
    cr_expect_eq(node_get_value(&a), 10,
        "node_get_value should return 10 after init(10)");
    cr_expect_eq(node_get_next(&a), NULL,
        "node_get_next should return NULL (native absence) after init");

    /* Caso 2: Inicializar otro nodo, enlazar y recorrer */
    Node b;
    node_init(&b, 20);
    node_set_next(&a, &b);
    cr_expect_eq(node_get_value(node_get_next(&a)), 20,
        "node_get_value(node_get_next(a)) should be 20 after set_next(a, b)");
    cr_expect_eq(node_get_next(&b), NULL,
        "node_get_next(b) should be NULL (b has no next)");
}

/* =========================================================================
 * LinkedList — 5 pasos sobre la misma instancia
 * ========================================================================= */

Test(data_structures_basics, linked_list_should_maintain_state_across_operations) {
    LinkedList list;
    int traversal[16];
    int len;

    /* Paso 1: Estado vacío */
    linked_list_init(&list);
    cr_expect(linked_list_is_empty(&list),
        "linked_list_is_empty should be true after init");
    cr_expect_eq((int)linked_list_size(&list), 0,
        "linked_list_size should be 0 after init");
    cr_expect_eq(linked_list_get_head(&list), -1,
        "linked_list_get_head should return FAILURE_VALUE (-1) when empty");

    /* Paso 2: Insertar por ambos extremos — insert_tail(10), insert_tail(20),
     *          insert_head(5), insert_tail(10)  →  5, 10, 20, 10 */
    linked_list_insert_tail(&list, 10);
    linked_list_insert_tail(&list, 20);
    linked_list_insert_head(&list, 5);
    linked_list_insert_tail(&list, 10);
    cr_expect_eq((int)linked_list_size(&list), 4,
        "linked_list_size should be 4 after four insertions");
    len = traverse_list(&list, traversal, 16);
    cr_expect_eq(len, 4,
        "traversal length should be 4");
    cr_expect_eq(traversal[0], 5,
        "traversal[0] should be 5");
    cr_expect_eq(traversal[1], 10,
        "traversal[1] should be 10");
    cr_expect_eq(traversal[2], 20,
        "traversal[2] should be 20");
    cr_expect_eq(traversal[3], 10,
        "traversal[3] should be 10");

    /* Paso 3: Eliminar primera aparición — delete(10)  →  5, 20, 10 */
    cr_expect_eq(linked_list_delete(&list, 10), 0,
        "linked_list_delete(10) should return 0 (success)");
    cr_expect_eq((int)linked_list_size(&list), 3,
        "linked_list_size should be 3 after delete(10)");
    len = traverse_list(&list, traversal, 16);
    cr_expect_eq(len, 3,
        "traversal length should be 3 after deleting first 10");
    cr_expect_eq(traversal[0], 5,
        "traversal[0] should be 5");
    cr_expect_eq(traversal[1], 20,
        "traversal[1] should be 20");
    cr_expect_eq(traversal[2], 10,
        "traversal[2] should be 10");

    /* Paso 4: Valor ausente — delete(99) */
    cr_expect_eq(linked_list_delete(&list, 99), -1,
        "linked_list_delete(99) should return FAILURE_VALUE (-1) for absent value");
    cr_expect_eq((int)linked_list_size(&list), 3,
        "linked_list_size should remain 3 after failed delete");

    /* Paso 5: Vaciar la lista — delete(5), delete(20), delete(10) */
    cr_expect_eq(linked_list_delete(&list, 5), 0,
        "linked_list_delete(5) should return 0 (success)");
    cr_expect_eq(linked_list_delete(&list, 20), 0,
        "linked_list_delete(20) should return 0 (success)");
    cr_expect_eq(linked_list_delete(&list, 10), 0,
        "linked_list_delete(10) should return 0 (success)");
    cr_expect(linked_list_is_empty(&list),
        "linked_list_is_empty should be true after emptying the list");
    cr_expect_eq((int)linked_list_size(&list), 0,
        "linked_list_size should be 0 after emptying the list");
    cr_expect_eq(linked_list_get_head(&list), -1,
        "linked_list_get_head should return FAILURE_VALUE (-1) when list is empty again");
}

/* =========================================================================
 * Stack — 4 pasos sobre la misma instancia
 * ========================================================================= */

Test(data_structures_basics, stack_should_maintain_lifo_state_across_operations) {
    Stack stack;

    /* Paso 1: Estado vacío y extracción fallida */
    stack_init(&stack);
    cr_expect(stack_is_empty(&stack),
        "stack_is_empty should be true after init");
    cr_expect_eq((int)stack_size(&stack), 0,
        "stack_size should be 0 after init");
    cr_expect_eq(stack_peek(&stack), -1,
        "stack_peek should return FAILURE_VALUE (-1) on empty stack");
    cr_expect_eq(stack_pop(&stack), -1,
        "stack_pop should return FAILURE_VALUE (-1) on empty stack");

    /* Paso 2: LIFO y peek no mutante — push(10), push(20), push(30), peek() */
    stack_push(&stack, 10);
    stack_push(&stack, 20);
    stack_push(&stack, 30);
    cr_expect_eq(stack_peek(&stack), 30,
        "stack_peek should return 30 (top) after push(10,20,30)");
    cr_expect_eq((int)stack_size(&stack), 3,
        "stack_size should be 3 after three pushes");

    /* Paso 3: Extracción y reutilización —
     *   pop() → 30; push(40); pop() → 40; pop() → 20; pop() → 10 */
    cr_expect_eq(stack_pop(&stack), 30,
        "stack_pop should return 30 (first pop)");
    stack_push(&stack, 40);
    cr_expect_eq(stack_pop(&stack), 40,
        "stack_pop should return 40 after push(40)");
    cr_expect_eq(stack_pop(&stack), 20,
        "stack_pop should return 20");
    cr_expect_eq(stack_pop(&stack), 10,
        "stack_pop should return 10 (last element)");
    cr_expect(stack_is_empty(&stack),
        "stack_is_empty should be true after all pops");
    cr_expect_eq((int)stack_size(&stack), 0,
        "stack_size should be 0 after all pops");

    /* Paso 4: Vacío tras extracción */
    cr_expect_eq(stack_pop(&stack), -1,
        "stack_pop should return FAILURE_VALUE (-1) on empty stack after drain");
    cr_expect(stack_is_empty(&stack),
        "stack_is_empty should still be true after pop on empty stack");
}

/* =========================================================================
 * Queue — 4 pasos sobre la misma instancia
 * ========================================================================= */

Test(data_structures_basics, queue_should_maintain_fifo_state_across_operations) {
    Queue queue;

    /* Paso 1: Estado vacío y extracción fallida */
    queue_init(&queue);
    cr_expect(queue_is_empty(&queue),
        "queue_is_empty should be true after init");
    cr_expect_eq((int)queue_size(&queue), 0,
        "queue_size should be 0 after init");
    cr_expect_eq(queue_peek(&queue), -1,
        "queue_peek should return FAILURE_VALUE (-1) on empty queue");
    cr_expect_eq(queue_dequeue(&queue), -1,
        "queue_dequeue should return FAILURE_VALUE (-1) on empty queue");

    /* Paso 2: FIFO y peek no mutante — enqueue(10), enqueue(20), enqueue(30), peek() */
    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);
    queue_enqueue(&queue, 30);
    cr_expect_eq(queue_peek(&queue), 10,
        "queue_peek should return 10 (front) after enqueue(10,20,30)");
    cr_expect_eq((int)queue_size(&queue), 3,
        "queue_size should be 3 after three enqueues");

    /* Paso 3: Extracción y reutilización —
     *   dequeue() → 10; enqueue(40); dequeue() → 20; dequeue() → 30; dequeue() → 40 */
    cr_expect_eq(queue_dequeue(&queue), 10,
        "queue_dequeue should return 10 (first dequeue)");
    queue_enqueue(&queue, 40);
    cr_expect_eq(queue_dequeue(&queue), 20,
        "queue_dequeue should return 20");
    cr_expect_eq(queue_dequeue(&queue), 30,
        "queue_dequeue should return 30");
    cr_expect_eq(queue_dequeue(&queue), 40,
        "queue_dequeue should return 40 (last enqueued)");
    cr_expect(queue_is_empty(&queue),
        "queue_is_empty should be true after all dequeues");
    cr_expect_eq((int)queue_size(&queue), 0,
        "queue_size should be 0 after all dequeues");

    /* Paso 4: Vacío tras extracción */
    cr_expect_eq(queue_dequeue(&queue), -1,
        "queue_dequeue should return FAILURE_VALUE (-1) on empty queue after drain");
    cr_expect(queue_is_empty(&queue),
        "queue_is_empty should still be true after dequeue on empty queue");
}

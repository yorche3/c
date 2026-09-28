# Data Structures Basics — C

Implementación de la especificación [06_Data_Structures_Basics](https://yorche3.github.io/programming_languages/core/algorithms/06_Data_Structures_Basics/) en **C99**, compilada con **GCC** y probada con **Criterion**.

Biblioteca con header público en `include/`, implementación en `src/` y pruebas unitarias en `test/`. Define un tipo `Node` compartido y tres ADTs independientes: `LinkedList`, `Stack` y `Queue`, todos implementados manualmente sobre el mismo `Node`.

Implementation of the [06_Data_Structures_Basics](https://yorche3.github.io/programming_languages/core/algorithms/06_Data_Structures_Basics/) specification in **C99**, compiled with **GCC** and tested with **Criterion**.

Library with a public header in `include/`, implementation in `src/`, and unit tests in `test/`. Defines a shared `Node` type and three independent ADTs: `LinkedList`, `Stack` and `Queue`, all implemented manually on the same `Node`.

---

## 📂 Archivos y estructura / Files & Structure

| Archivo / File | Propósito / Purpose |
|---|---|
| [`include/data_structures_basics.h`](include/data_structures_basics.h) | Header público — declara `Node`, `LinkedList`, `Stack`, `Queue` y sus 20 funciones / Public header — declares `Node`, `LinkedList`, `Stack`, `Queue` and their 20 functions |
| [`src/data_structures_basics.c`](src/data_structures_basics.c) | Implementación — los cuatro tipos y todas sus operaciones con contratos documentados / Implementation — all four types and their operations with documented contracts |
| [`test/data_structures_basics_test.c`](test/data_structures_basics_test.c) | Suite Criterion — 4 tests, pasos sucesivos sobre la misma instancia por ADT / Criterion suite — 4 tests, successive steps on the same instance per ADT |
| [`Makefile`](Makefile) | Automatización de compilación y tests / Build and test automation |
| [`.gitignore`](.gitignore) | Ignora `obj/` y `bin/` / Ignores `obj/` and `bin/` |

**Estructura de directorios / Directory structure:**

```text
data_structures_basics/
├── include/
│   └── data_structures_basics.h    # Header público — tipos y 20 funciones
├── src/
│   └── data_structures_basics.c    # Implementación — Node, LinkedList, Stack, Queue
├── test/
│   └── data_structures_basics_test.c  # Suite Criterion — 4 tests
├── Makefile                         # Automatización de compilación
├── .gitignore                       # Ignora obj/, bin/
├── obj/                             # Objetos compilados (generado)
├── bin/                             # Ejecutable de tests (generado)
└── README.md                        # Este archivo
```

> **Nota de desviación / Deviation note:** La especificación propone `src/data_structures_basics.c` + `test/data_structures_basics_test.c` + `test/run_tests.ext`. Esta implementación añade `include/data_structures_basics.h` para el contrato público (convención idiomática de C: encabezado separado) y no tiene `run_tests.ext` porque Criterion descubre los tests automáticamente al ejecutar el binario compilado. El layout `include/` + `src/` + `test/` sigue el mismo patrón que `naive_sort` y el módulo `numbers` de Foundations.
>
> **Deviation note:** The specification proposes `src/data_structures_basics.c` + `test/data_structures_basics_test.c` + `test/run_tests.ext`. This implementation adds `include/data_structures_basics.h` for the public contract (C's idiomatic convention: separate header) and has no `run_tests.ext` because Criterion discovers tests automatically when running the compiled binary. The `include/` + `src/` + `test/` layout follows the same pattern as `naive_sort` and the `numbers` module from Foundations.

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** Mismo patrón de biblioteca que [`naive_sort`](../naive_sort/README.md): un header público, una implementación y tests en `test/` descubiertos automáticamente por Criterion. En C los ADTs se implementan con `struct` y funciones con prefijo de tipo (`node_`, `linked_list_`, `stack_`, `queue_`). La ausencia de espacios de nombres hace que el prefijo sea la convención idiomática para separar el contrato de cada tipo.

**EN:** Same library pattern as [`naive_sort`](../naive_sort/README.md): a public header, an implementation and tests in `test/` auto-discovered by Criterion. In C, ADTs are implemented with `struct` and type-prefixed functions (`node_`, `linked_list_`, `stack_`, `queue_`). The absence of namespaces makes the prefix the idiomatic convention to separate each type's contract.

---

## 📄 Configuración clave / Key Configuration

### `include/data_structures_basics.h` — Header público

```c
typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct { Node *head; Node *tail; size_t count; } LinkedList;
typedef struct { Node *top;  size_t count; } Stack;
typedef struct { Node *front; Node *rear; size_t count; } Queue;
```

`<stdbool.h>` aporta `bool` para `is_empty`; `<stdddef.h>` aporta `size_t` para los contadores; `<stdlib.h>` aporta `malloc`/`free` en la implementación (no en el header).

### `Makefile`

| Variable | Valor |
|---|---|
| `CC` | `gcc` |
| `CFLAGS` | `-Wall -Wextra -std=c99 -Iinclude` |
| `LDFLAGS` | `$(shell pkg-config --cflags --libs criterion)` |
| `TEST_BIN` | `bin/run_tests` |

---

## 🚀 Compilación y ejecución / Build & Run

### Requisito / Requirement

```bash
# Linux (Debian/Ubuntu)
sudo apt install gcc make libcriterion-dev
```

### Objetivos del Makefile / Makefile targets

```bash
make         # Alias de test / alias for test
make build   # Solo compila la biblioteca / build the library only
make test    # Compila y ejecuta los tests / compile and run the tests
make clean   # Limpia obj/ y bin/ / clean obj/ and bin/
```

**Salida real / Actual output:**

```text
rm -rf obj bin
mkdir -p obj
mkdir -p bin
gcc -Wall -Wextra -std=c99 -Iinclude -c -o obj/data_structures_basics.o src/data_structures_basics.c
gcc -Wall -Wextra -std=c99 -Iinclude -c -o obj/data_structures_basics_test.o test/data_structures_basics_test.c
gcc -Wall -Wextra -std=c99 -Iinclude -o bin/run_tests obj/data_structures_basics.o obj/data_structures_basics_test.o -pthread -DBXF_STATIC_LIB=1 -lcriterion
./bin/run_tests
[====] Synthesis: Tested: 4 | Passing: 4 | Failing: 0 | Crashing: 0
```

> **ES:** La compilación no emite warnings con `-Wall -Wextra -std=c99`.
> **EN:** The build emits no warnings with `-Wall -Wextra -std=c99`.

---

## 🧠 Algoritmos y operaciones / Algorithms & Operations

| Operación / Operation | Entrada → salida / Input → output | Complejidad / Complexity | Notas / Notes |
|---|---|---|---|
| `node_init(node, value)` | `(Node*, int) → void` | `O(1)` | Asigna `value` y `next = NULL` / Sets `value` and `next = NULL` |
| `node_get_value(node)` | `(const Node*) → int` | `O(1)` | Devuelve `-1` si `node == NULL` / Returns `-1` if `node == NULL` |
| `node_get_next(node)` | `(const Node*) → Node*` | `O(1)` | Devuelve `NULL` si `node == NULL` / Returns `NULL` if `node == NULL` |
| `node_set_next(node, next)` | `(Node*, Node*) → void` | `O(1)` | No-op si `node == NULL` |
| `linked_list_init(list)` | `(LinkedList*) → void` | `O(1)` | `head = tail = NULL`, `count = 0` |
| `linked_list_is_empty(list)` | `(const LinkedList*) → bool` | `O(1)` | `true` si `list == NULL` o `count == 0` |
| `linked_list_size(list)` | `(const LinkedList*) → size_t` | `O(1)` | `0` si `list == NULL` |
| `linked_list_get_head(list)` | `(const LinkedList*) → int` | `O(1)` | `-1` si vacía o `NULL` / `-1` if empty or `NULL` |
| `linked_list_get_head_node(list)` | `(const LinkedList*) → Node*` | `O(1)` | Nodo cabeza para recorrer la lista / Head node for traversal |
| `linked_list_insert_head(list, value)` | `(LinkedList*, int) → void` | `O(1)` | `malloc` del nodo; `count++` |
| `linked_list_insert_tail(list, value)` | `(LinkedList*, int) → void` | `O(1)` | `malloc` del nodo; `count++` |
| `linked_list_delete(list, value)` | `(LinkedList*, int) → int` | `O(n)` | `0` en éxito; `-1` si no encontrado; libera el nodo con `free` |
| `stack_init(stack)` | `(Stack*) → void` | `O(1)` | `top = NULL`, `count = 0` |
| `stack_is_empty(stack)` | `(const Stack*) → bool` | `O(1)` | `true` si `stack == NULL` o `top == NULL` |
| `stack_size(stack)` | `(const Stack*) → size_t` | `O(1)` | `0` si `stack == NULL` |
| `stack_push(stack, value)` | `(Stack*, int) → void` | `O(1)` | `malloc` del nodo; nuevo `top`; `count++` |
| `stack_pop(stack)` | `(Stack*) → int` | `O(1)` | Valor extraído; `free` del nodo; `-1` si vacía |
| `stack_peek(stack)` | `(const Stack*) → int` | `O(1)` | Valor de `top` sin extraer; `-1` si vacía |
| `queue_init(queue)` | `(Queue*) → void` | `O(1)` | `front = rear = NULL`, `count = 0` |
| `queue_is_empty(queue)` | `(const Queue*) → bool` | `O(1)` | `true` si `queue == NULL` o `front == NULL` |
| `queue_size(queue)` | `(const Queue*) → size_t` | `O(1)` | `0` si `queue == NULL` |
| `queue_enqueue(queue, value)` | `(Queue*, int) → void` | `O(1)` | `malloc` del nodo; nuevo `rear`; `count++` |
| `queue_dequeue(queue)` | `(Queue*) → int` | `O(1)` | Valor extraído de `front`; `free` del nodo; `-1` si vacía |
| `queue_peek(queue)` | `(const Queue*) → int` | `O(1)` | Valor de `front` sin extraer; `-1` si vacía |

---

## 🧩 Decisiones de diseño / Design decisions

| Decisión / Decision | Alternativa considerada / Alternative | Razón / Reason |
|---|---|---|
| `Node` como `struct` con `int value` y `struct Node *next` | `void *` genérico para el valor | La especificación fija el dominio en enteros positivos; `int` evita la indirección y simplifica los tests sin perder el contrato |
| Instancias de ADTs en la pila (`Node a; linked_list_init(&a)`) | `malloc` para los ADTs contenedores | Coincide con la semántica de la especificación: declarar primero, luego inicializar; la gestión en la pila es la que C favorece para objetos de duración conocida |
| `linked_list_get_head_node` como función auxiliar del contrato | Acceso directo a `list->head` en los tests | Los tests deben observar la estructura solo a través de operaciones del contrato; esta función expone el nodo de entrada para el recorrido sin revelar el campo interno |
| `FAILURE_VALUE = -1` centralizado en un `#define` | Literal `-1` disperso | Facilita el cambio en un solo punto y hace explícito que `-1` es el indicador de fallo del módulo, no un valor de dominio |

---

## 🔀 Adaptaciones idiomáticas / Idiomatic adaptations

| Especificación / Specification | Adaptación / Adaptation | Justificación / Justification |
|---|---|---|
| `Node.init(value)` como método de tipo; `node = Node.init(value)` devuelve instancia | `node_init(Node *node, int value)` — función con prefijo de tipo; la instancia la declara el llamador antes de `node_init` | C no tiene métodos ni constructores; el prefijo `node_` es la convención de espacio de nombres. La instancia puede vivir en la pila (sin `malloc`) o en el heap según decida el llamador |
| `node.set_next(next)` devuelve `this` o un nodo nuevo | `node_set_next(Node *node, Node *next)` devuelve `void` | C es imperativo y mutable; la operación actualiza el campo directamente sin necesidad de devolver nada |
| `linked_list_delete` devuelve `success`/`failure` (semántica booleana) | Devuelve `0` (éxito) y `-1` (`FAILURE_VALUE`) como `int` | C no tiene tipo de resultado booleano para operaciones: `int` con el centinela `-1` es el indicador natural del lenguaje, compatible con las demás operaciones del módulo |
| `insert_head`/`insert_tail` sin límite de capacidad | `malloc` para cada nodo insertado; gestión de memoria manual | C no tiene asignador automático; `malloc` es la forma idiomática de heap dinámico. El módulo no impone límite artificial: falla silenciosamente si `malloc` devuelve `NULL` (agotamiento del sistema, no un caso normal del contrato) |
| Layout `src/` + `test/` + `test/run_tests.ext` | Layout `include/` + `src/` + `test/` sin `run_tests.ext` separado | C idiomático separa la interfaz pública en un header (`include/`). Criterion descubre y ejecuta los tests automáticamente desde el binario compilado, eliminando la necesidad de un `run_tests.ext` manual |

---

## 🚨 Indicadores de fallo / Failure indicators

| Operación / Operation | Situación de fallo / Failure situation | Indicador / Indicator | Ejemplo / Example |
|---|---|---|---|
| `node_get_value(node)` | `node == NULL` | `-1` (`FAILURE_VALUE`) | `node_get_value(NULL)` → `-1` |
| `node_get_next(node)` | `node == NULL` | `NULL` | `node_get_next(NULL)` → `NULL` |
| `node_get_next(node)` | Nodo sin siguiente / Node has no next | `NULL` (ausencia nativa) | `node_get_next(&b)` → `NULL` tras `node_init(&b, 20)` |
| `linked_list_get_head(list)` | Lista vacía o `list == NULL` | `-1` (`FAILURE_VALUE`) | `linked_list_get_head(&list)` tras `init` → `-1` |
| `linked_list_delete(list, value)` | Valor no encontrado o lista vacía | `-1` (`FAILURE_VALUE`) | `linked_list_delete(&list, 99)` → `-1` |
| `stack_pop(stack)` | Pila vacía o `stack == NULL` | `-1` (`FAILURE_VALUE`) | `stack_pop(&stack)` tras `init` → `-1` |
| `stack_peek(stack)` | Pila vacía o `stack == NULL` | `-1` (`FAILURE_VALUE`) | `stack_peek(&stack)` tras `init` → `-1` |
| `queue_dequeue(queue)` | Cola vacía o `queue == NULL` | `-1` (`FAILURE_VALUE`) | `queue_dequeue(&queue)` tras `init` → `-1` |
| `queue_peek(queue)` | Cola vacía o `queue == NULL` | `-1` (`FAILURE_VALUE`) | `queue_peek(&queue)` tras `init` → `-1` |

> **ES:** El indicador de fallo entero es `-1` para todas las operaciones que devuelven `int`. El indicador de ausencia de enlace es `NULL` para las que devuelven `Node *`. Los valores de prueba son enteros positivos (5, 10, 20, 30, 40) que no colisionan con ninguno de los dos indicadores.
>
> **EN:** The integer failure indicator is `-1` for all operations returning `int`. The link absence indicator is `NULL` for those returning `Node *`. Test values are positive integers (5, 10, 20, 30, 40) that do not collide with either indicator.

---

## ✅ Cobertura de pruebas / Test coverage

| Caso de la especificación / Specification case | Cubierto / Covered | Prueba / Test | Notas / Notes |
|---|---|:--:|---|
| Node — Inicializar y observar valor/enlace | Sí | `node_should_init_and_observe_value_and_link` | Verifica `get_value = 10`, `get_next = NULL` |
| Node — Inicializar otro nodo, enlazar y recorrer | Sí | `node_should_init_and_observe_value_and_link` | Verifica `get_value(get_next(a)) = 20`; `get_next(b) = NULL` |
| LinkedList — Estado vacío | Sí | `linked_list_should_maintain_state_across_operations` | `is_empty = true`, `size = 0`, `get_head = -1` |
| LinkedList — Insertar por ambos extremos | Sí | `linked_list_should_maintain_state_across_operations` | `size = 4`; recorrido: 5, 10, 20, 10 |
| LinkedList — Eliminar primera aparición | Sí | `linked_list_should_maintain_state_across_operations` | `delete(10)` → éxito; recorrido: 5, 20, 10; `size = 3` |
| LinkedList — Valor ausente | Sí | `linked_list_should_maintain_state_across_operations` | `delete(99)` → `-1`; size no cambia |
| LinkedList — Vaciar la lista | Sí | `linked_list_should_maintain_state_across_operations` | Tres `delete` exitosos; `is_empty = true`; `get_head = -1` |
| Stack — Estado vacío y extracción fallida | Sí | `stack_should_maintain_lifo_state_across_operations` | `is_empty = true`, `size = 0`, `peek = -1`, `pop = -1` |
| Stack — LIFO y `peek` no mutante | Sí | `stack_should_maintain_lifo_state_across_operations` | `peek = 30`, `size = 3` tras `push(10, 20, 30)` |
| Stack — Extracción y reutilización | Sí | `stack_should_maintain_lifo_state_across_operations` | `pop` → 30, 40, 20, 10; `is_empty = true` |
| Stack — Vacío tras extracción | Sí | `stack_should_maintain_lifo_state_across_operations` | `pop` → `-1`; `is_empty` sigue `true` |
| Queue — Estado vacío y extracción fallida | Sí | `queue_should_maintain_fifo_state_across_operations` | `is_empty = true`, `size = 0`, `peek = -1`, `dequeue = -1` |
| Queue — FIFO y `peek` no mutante | Sí | `queue_should_maintain_fifo_state_across_operations` | `peek = 10`, `size = 3` tras `enqueue(10, 20, 30)` |
| Queue — Extracción y reutilización | Sí | `queue_should_maintain_fifo_state_across_operations` | `dequeue` → 10, 20, 30, 40; `is_empty = true` |
| Queue — Vacío tras extracción | Sí | `queue_should_maintain_fifo_state_across_operations` | `dequeue` → `-1`; `is_empty` sigue `true` |

**Total: 4 tests — 15 pasos de especificación cubiertos — 0 omitidos.**

---

## ⚠️ Limitaciones conocidas / Known limitations

| Limitación / Limitation | Impacto / Impact | Alternativa o plan / Workaround or plan |
|---|---|---|
| `malloc` silencioso ante agotamiento de memoria | Si el sistema agota el heap, `insert_head`/`insert_tail`/`push`/`enqueue` fallan silenciosamente (no insertan, no ajustan `count`) | El contrato de Fase 1 no incluye excepciones ni `errno`; el manejo explícito de `malloc == NULL` llegará en Fase 2. Los tests no prueban este caso porque requeriría agotar el heap artificialmente |
| `FAILURE_VALUE = -1` colisiona con el dominio si se usan enteros negativos | Si el llamador inserta `-1`, `get_head`/`pop`/`peek`/`dequeue` no permiten distinguir éxito de fallo | La especificación restringe los valores de prueba a enteros positivos. El README del lenguaje lo documenta como la restricción del indicador de C en Fase 1 |

---

## 📝 Notas de implementación / Implementation Notes

### 🧱 `Node` compartido / Shared `Node`

El mismo `struct Node { int value; struct Node *next; }` es el nodo de `LinkedList`, `Stack` y `Queue`. Cada ADT mantiene solo sus propios punteros (`head`/`tail`, `top`, `front`/`rear`) y su contador `count`. No hay delegación de `Stack` o `Queue` hacia `LinkedList`.

The same `struct Node { int value; struct Node *next; }` is the node for `LinkedList`, `Stack` and `Queue`. Each ADT keeps only its own pointers (`head`/`tail`, `top`, `front`/`rear`) and its `count`. There is no delegation from `Stack` or `Queue` to `LinkedList`.

### 🧩 Contrato en C / Contract in C

El contrato se declara en `include/data_structures_basics.h` como header público con las firmas de las 20 funciones. Esta es la forma idiomática de C (encabezado con tipo opaco o incompleto): separa «qué hace» de «cómo lo hace» sin necesitar `interface` ni `trait`, que solo tendrían sentido con más de una implementación.

The contract is declared in `include/data_structures_basics.h` as a public header with the 20 function signatures. This is C's idiomatic form (header with opaque or incomplete type): it separates "what it does" from "how it does it" without needing `interface` or `trait`, which would only make sense with more than one implementation.

### 🧪 Estructura de las pruebas / Test structure

Los 4 tests son pasos sucesivos sobre la misma instancia del ADT, tal como indica la especificación. El helper `traverse_list` recorre la lista usando solo operaciones del contrato (`linked_list_get_head_node`, `node_get_value`, `node_get_next`), sin acceder a los campos internos de `LinkedList`.

The 4 tests are successive steps on the same ADT instance, as the specification states. The `traverse_list` helper traverses the list using only contract operations (`linked_list_get_head_node`, `node_get_value`, `node_get_next`), without accessing `LinkedList`'s internal fields.

### 💾 Gestión de memoria / Memory management

`insert_head`, `insert_tail`, `push` y `enqueue` usan `malloc` para el nodo nuevo. `linked_list_delete`, `stack_pop` y `queue_dequeue` liberan el nodo extraído con `free`. Los tests de Criterion se ejecutan en subprocesos separados, lo que implica que la memoria no liberada al final de un test queda contenida en ese subproceso y no interfiere con los demás.

`insert_head`, `insert_tail`, `push` and `enqueue` use `malloc` for the new node. `linked_list_delete`, `stack_pop` and `queue_dequeue` free the extracted node with `free`. Criterion tests run in separate subprocesses, so memory not freed at the end of a test is contained in that subprocess and does not interfere with others.

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

This project is also implemented in other languages. Explore the [main repository](https://github.com/yorche3/programming_languages) to see all the versions.

---

## 🔍 Checklist de validación / Validation checklist

- [x] La suite nativa se ejecutó y su salida real está copiada en este README.
- [x] Cada caso de la especificación tiene su fila en _Cobertura de pruebas_ (o `Omitido` con razón).
- [x] Cada desviación del pseudocódigo o de la ubicación esperada está en _Adaptaciones idiomáticas_.
- [x] Cada operación con fallo posible está en _Indicadores de fallo_.
- [x] No hay rutas absolutas del autor, credenciales ni salidas inventadas.
- [x] Los enlaces relativos resuelven dentro del repositorio y el documento es bilingüe.
- [x] Ninguna sección repite lo que ya dice la especificación.

---

## 📚 Referencias / References

| Tipo / Kind | Referencia / Reference |
|---|---|
| Especificación / Specification | [`06_Data_Structures_Basics.md`](../../../../../docs/core/algorithms/06_Data_Structures_Basics.md) |
| Módulo homologado del lenguaje / Homologated module | [`c/core/algorithms/naive_sort/`](../naive_sort/README.md) |
| Guía de inicialización / Initialisation guide | [`core/00_Project_Initialization_Guide.md`](../../../../../docs/core/00_Project_Initialization_Guide.md) |
| Adaptaciones idiomáticas / Idiomatic adaptations | [`AGENT_Template.md`](../../../../../docs/AGENT_Template.md) |
| Validación de la documentación / Documentation validation | [`WORKFLOW.md`](../../../../../docs/WORKFLOW.md) |
| Documentación oficial del lenguaje / Language official docs | [gcc.gnu.org](https://gcc.gnu.org/onlinedocs/) · [criterion-test.readthedocs.io](https://criterion-test.readthedocs.io/en/latest/) |

---

*[← Volver a Algorithms Pure](../README.md) | [↑ Volver a Core](../../README.md)*

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*

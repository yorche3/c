# Data Structures Advanced — C

Implementación de la especificación [07_Data_Structures_Advanced](https://yorche3.github.io/programming_languages/core/algorithms/07_Data_Structures_Advanced/) en **C99**, compilada con **GCC** y probada con **Criterion**.

Biblioteca con header público en `include/`, implementación en `src/` y pruebas unitarias parametrizadas en `test/`. Implementa `TreeNode` y un árbol binario de búsqueda (`BinaryTree`), así como una lista de adyacencia ordenada manual y un grafo dirigido (`Graph`), ambos utilizando valor embebido según el contrato.

Implementation of the [07_Data_Structures_Advanced](https://yorche3.github.io/programming_languages/core/algorithms/07_Data_Structures_Advanced/) specification in **C99**, compiled with **GCC** and tested with **Criterion**.

Library with a public header in `include/`, implementation in `src/`, and parameterized unit tests in `test/`. Implements `TreeNode` and a binary search tree (`BinaryTree`), along with a manual sorted adjacency list and directed graph (`Graph`), both using embedded values per the contract.

---

## 📂 Archivos y estructura / Files & Structure

| Archivo / File | Propósito / Purpose |
|---|---|
| [`include/data_structures_advanced.h`](include/data_structures_advanced.h) | Header público — declara `TreeNode`, `BinaryTree`, `NeighborNode`, `GraphNode`, `Graph` y sus funciones públicas / Public header — declares `TreeNode`, `BinaryTree`, `NeighborNode`, `GraphNode`, `Graph` and their public functions |
| [`src/data_structures_advanced.c`](src/data_structures_advanced.c) | Implementación — ABB y Grafo dirigido con gestión manual de memoria y adyacencia ordenada / Implementation — BST and Directed Graph with manual memory management and sorted adjacency |
| [`test/data_structures_advanced_test.c`](test/data_structures_advanced_test.c) | Suite Criterion — 153 pruebas parametrizadas cubriendo todas las operaciones y casos de prueba / Criterion suite — 153 parameterized tests covering all operations and test cases |
| [`Makefile`](Makefile) | Automatización de compilación y ejecución de pruebas / Build and test automation |
| [`.gitignore`](.gitignore) | Ignora artefactos generados `obj/` y `bin/` / Ignores generated build artifacts `obj/` and `bin/` |

**Estructura de directorios / Directory structure:**

```text
data_structures_advanced/
├── include/
│   └── data_structures_advanced.h       # Header público / Public header
├── src/
│   └── data_structures_advanced.c       # Implementación BST y Graph / BST & Graph implementation
├── test/
│   └── data_structures_advanced_test.c  # Suite Criterion parametrizada (153 tests)
├── Makefile                            # Automatización de compilación / Build automation
├── .gitignore                          # Exclusiones de Git / Git exclusions
├── obj/                                # Archivos objeto compilados (generado) / Object files (generated)
├── bin/                                # Binario ejecutable de pruebas (generado) / Test binary (generated)
└── README.md                           # Este archivo / This file
```

> **Nota de desviación / Deviation note:** La especificación propone `src/data_structures_advanced.ext` + `test/data_structures_advanced_test.ext` + `test/run_tests.ext`. Esta implementación añade `include/data_structures_advanced.h` para el contrato público (convención idiomática de C: cabecera separada) y no requiere un script `run_tests.ext` separado ya que Criterion genera el punto de entrada ejecutable directamente en `bin/run_tests`.
>
> **Deviation note:** The specification proposes `src/data_structures_advanced.ext` + `test/data_structures_advanced_test.ext` + `test/run_tests.ext`. This implementation adds `include/data_structures_advanced.h` for the public contract (C idiomatic convention: separate header) and does not require a separate `run_tests.ext` script because Criterion builds the test executable entry point directly into `bin/run_tests`.

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** Proyecto modular en C99 estructurado manualmente. En C, al carecer de herencia de clases a nivel de lenguaje, se adopta la forma de **valor embebido** (`int value` / `int label`) directamente en `TreeNode` y `GraphNode`, tal como autoriza la especificación. La colección de vecinos y el registro de vértices del grafo se construyen de forma totalmente manual mediante listas enlazadas dedicadas (`NeighborNode` y `GraphNode`), manteniendo la adyacencia ordenada ascendentemente en `O(d(u))` sin recurrir a mapas, árboles ni contenedores externos.

**EN:** Modular C99 project structured manually. Because C lacks class-based inheritance, the **embedded value** pattern (`int value` / `int label`) is adopted directly within `TreeNode` and `GraphNode`, as allowed by the specification. Neighbour storage and vertex registry are built manually using dedicated singly-linked lists (`NeighborNode` and `GraphNode`), maintaining sorted ascending adjacency in `O(d(u))` without relying on external maps, trees, or containers.

---

## 📄 Configuración clave / Key Configuration

### `include/data_structures_advanced.h` — Header público

```c
typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct BinaryTree {
    TreeNode *root;
    size_t count;
} BinaryTree;

typedef struct NeighborNode {
    int label;
    struct NeighborNode *next;
} NeighborNode;

typedef struct GraphNode {
    int label;
    NeighborNode *neighbours;
    struct GraphNode *next_vertex;
} GraphNode;

typedef struct Graph {
    GraphNode *vertices;
    size_t vertex_total;
    size_t edges;
} Graph;
```

### `Makefile`

| Variable | Valor |
|---|---|
| `CC` | `gcc` |
| `CFLAGS` | `-Wall -Wextra -std=c99 -Iinclude` |
| `LDFLAGS` | `-pthread -DBXF_STATIC_LIB=1 -lcriterion` |
| `TEST_BIN` | `bin/run_tests` |

---

## 🚀 Compilación y ejecución / Build & Run

### Requisitos / Requirements

```bash
# Linux (Debian/Ubuntu)
sudo apt install gcc make libcriterion-dev
```

### Comandos / Commands

```bash
make clean
make test
```

**Salida real / Actual output:**

```text
rm -rf obj bin
mkdir -p obj
mkdir -p bin
gcc -Wall -Wextra -std=c99 -Iinclude -c -o obj/data_structures_advanced.o src/data_structures_advanced.c
gcc -Wall -Wextra -std=c99 -Iinclude -c -o obj/data_structures_advanced_test.o test/data_structures_advanced_test.c
gcc -Wall -Wextra -std=c99 -Iinclude -o bin/run_tests obj/data_structures_advanced.o obj/data_structures_advanced_test.o -pthread -DBXF_STATIC_LIB=1 -lcriterion 
./bin/run_tests
[====] Synthesis: Tested: 153 | Passing: 153 | Failing: 0 | Crashing: 0 
```

---

## 🧠 Algoritmos y operaciones / Algorithms & Operations

| Operación / Operation | Entrada → salida / Input → output | Complejidad / Complexity | Notas / Notes |
|---|---|---|---|
| `tree_node_init` | `(TreeNode*, int) → void` | `O(1)` | Inicializa nodo con valor embebido y enlaces `NULL` / Initializes node with embedded value and `NULL` links |
| `tree_node_get_value` | `const TreeNode* → int` | `O(1)` | Lee el valor del nodo / Reads node value |
| `tree_node_get_left` / `get_right` | `const TreeNode* → TreeNode*` | `O(1)` | Retorna hijo izquierdo/derecho o `NULL` / Returns left/right child or `NULL` |
| `tree_node_set_left` / `set_right` | `(TreeNode*, TreeNode*) → void` | `O(1)` | Actualiza enlace izquierdo/derecho / Updates left/right link |
| `binary_tree_init` | `BinaryTree* → void` | `O(1)` | Inicializa árbol vacío (`root = NULL`, `count = 0`) / Initializes empty BST |
| `binary_tree_insert` | `(BinaryTree*, int) → int` | `O(h)` | Inserción iterativa en ABB; duplicado no altera tamaño; retorno 0 éxito / Iterative BST insertion; duplicates do not increment size; returns 0 on success |
| `binary_tree_contains` | `(const BinaryTree*, int) → bool` | `O(h)` | Búsqueda guiada por invariante BST / Search guided by BST invariant |
| `binary_tree_is_empty` | `const BinaryTree* → bool` | `O(1)` | Comprueba si `count == 0` / Checks if `count == 0` |
| `binary_tree_size` | `const BinaryTree* → size_t` | `O(1)` | Retorna número de nodos únicos / Returns count of unique nodes |
| `binary_tree_free` | `BinaryTree* → void` | `O(n)` | Libera todos los nodos recursivamente y reinicia estado / Recursively frees all nodes and resets state |
| `graph_init` | `Graph* → void` | `O(1)` | Inicializa grafo vacío (`vertices = NULL`, contadores a 0) / Initializes empty graph |
| `graph_add_vertex` | `(Graph*, int) → int` | `O(V)` | Añade vértice si no existe; idempotente; 0 éxito / Adds vertex if missing; idempotent; 0 on success |
| `graph_add_edge` | `(Graph*, int, int) → int` | `O(V + d(u))` | Requiere extremos existentes; inserta ordenado en vecinos; bucles permitidos; duplicado idempotente / Requires existing endpoints; sorted insertion in neighbours; loops allowed; idempotent duplicates |
| `graph_has_edge` | `(const Graph*, int, int) → bool` | `O(V + d(u))` | Búsqueda lineal en registro y lista ordenada de vecinos / Linear search in registry and sorted neighbour list |
| `graph_get_neighbors` | `(const Graph*, int, int**, size_t*) → int` | `O(V + d(u))` | Retorna copia dinámica en array de vecinos; 0 éxito, -1 fallo / Returns dynamically allocated array copy of neighbours; 0 on success, -1 on failure |
| `graph_is_empty` | `const Graph* → bool` | `O(1)` | Comprueba si `vertex_total == 0` / Checks if `vertex_total == 0` |
| `graph_vertex_count` | `const Graph* → size_t` | `O(1)` | Retorna total de vértices / Returns total vertices |
| `graph_edge_count` | `const Graph* → size_t` | `O(1)` | Retorna total de aristas / Returns total edges |
| `graph_free` | `Graph* → void` | `O(V + E)` | Libera vértices y listas de vecinos / Frees all vertices and neighbour lists |

---

## 🧩 Decisiones de diseño / Design decisions

| Decisión / Decision | Alternativa considerada / Alternative | Razón / Reason |
|---|---|---|
| Valor embebido en `TreeNode` y `GraphNode` | Herencia basada en `struct Node` base como primer miembro | C no tiene herencia nativa; embeber `value`/`label` directamente simplifica la memoria y acceso sin conversiones de punteros riesgosas |
| Almacenamiento manual de vecinos (`NeighborNode`) | Uso de una lista enlazada genérica o `void*` | Evita indirecciones adicionales y casteo de tipos; optimiza localidad y claridad de inserción ordenada en C puro |
| Copia dinámica (`int*`) en `graph_get_neighbors` | Retornar puntero interno a `NeighborNode*` | Garantiza el aislamiento estricto exigido por la especificación: modificar el resultado recibido no corrompe la estructura del grafo |
| Códigos de retorno enteros (`0` / `-1`) | Señalización mediante centinelas o variables globales (`errno`) | Modelo canónico en C para indicar éxito o fallo de forma inequívoca en operaciones que mutan o consultan memoria |

---

## 🔀 Adaptaciones idiomáticas / Idiomatic adaptations

| Especificación / Specification | Adaptación / Adaptation | Justificación / Justification |
|---|---|---|
| Base `Node(value)` con reutilización | Valor embebido (`int value` / `int label`) en `TreeNode` y `GraphNode` | C99 no soporta herencia orientada a objetos; la especificación permite explícitamente valor embebido |
| Enlaces ausentes representados por ausencia genérica | Puntero `NULL` en punteros de enlaces y nodos | En C `NULL` es la representación canónica y unívoca de puntero ausente o nulo |
| Retorno de secuencia de vecinos con aislamiento | `graph_get_neighbors(graph, u, &neighbors, &count)` asignando buffer con `malloc` | En C un array devuelto por valor no es nativo; pasar doble puntero y tamaño preserva aislamiento y requiere liberación del llamador (`free`) |
| Adaptación inmutable de `set_left`/`set_right` | No aplicable / Not applicable (mutación in-place) | C maneja estructuras mutables por puntero; la variante inmutable aplica solo a lenguajes funcionales puros |

---

## 🚨 Indicadores de fallo / Failure indicators

| Operación / Operation | Situación de fallo / Failure situation | Indicador / Indicator | Ejemplo / Example |
|---|---|---|---|
| `tree_node_init` | Entrada nula o puntero inválido | No aplica / Undefined behavior | Puntero `TreeNode*` debe ser válido según contrato C |
| `tree_node_get_left` / `get_right` | Enlace ausente o no inicializado | `NULL` | Retorna `NULL` si no hay hijo |
| `binary_tree_insert` | Fallo de asignación de memoria (`malloc`) | `-1` | Retorna `-1` si falla `malloc` |
| `binary_tree_contains` | Valor ausente o árbol vacío | `false` | `binary_tree_contains(&tree, 99) == false` |
| `graph_add_vertex` | Fallo de asignación de memoria (`malloc`) | `-1` | Retorna `-1` si falla `malloc` |
| `graph_add_edge` | Extremo `u` o `v` inexistente, o fallo de memoria | `-1` | `graph_add_edge(&graph, 10, 99) == -1` |
| `graph_has_edge` | Vértice origen/destino inexistente o arista ausente | `false` | `graph_has_edge(&graph, 10, 99) == false` |
| `graph_get_neighbors` | Vértice `u` inexistente en el grafo | `-1` | `graph_get_neighbors(&graph, 99, &out, &cnt) == -1` (salidas no se modifican) |

---

## ✅ Cobertura de pruebas / Test coverage

| Caso de la especificación / Specification case | Cubierto / Covered | Prueba / Test | Notas / Notes |
|---|---|:--:|---|
| `TreeNode`: Crear un nodo de árbol | Sí | `tree_node_init_should_satisfy_contract` / case `create_node` | Comprueba `tree_node_get_value(node) == 10` |
| `TreeNode`: Enlaces iniciales ausentes | Sí | `tree_node_init_should_satisfy_contract` / case `absent_links` | Comprueba `left == NULL` y `right == NULL` |
| `TreeNode`: Enlazar dos hijos | Sí | `tree_node_set_left_should_satisfy_contract`, `tree_node_set_right_should_satisfy_contract` / case `link_children` | Verifica enlaces a 20 y 30 |
| `TreeNode`: Recorrer cada enlace | Sí | `tree_node_get_left_should_satisfy_contract`, `tree_node_get_right_should_satisfy_contract` / case `traverse_links` | Sigue enlaces y verifica valores e hijos ausentes |
| `TreeNode`: Desenlazar hijos | Sí | `tree_node_set_left_should_satisfy_contract`, `tree_node_set_right_should_satisfy_contract` / case `unlink_children` | Comprueba persistencia tras desenlazar izquierdo y derecho |
| `TreeNode`: Adaptación inmutable | Omitido | No aplica / Not applicable | En C los nodos se mutan in-place vía punteros; la variante inmutable aplica a lenguajes funcionales |
| `BinaryTree`: Crear vacío | Sí | `binary_tree_init_should_satisfy_contract` / case `empty_tree` | `is_empty == true`, `size == 0`, `contains(50) == false` |
| `BinaryTree`: Insertar la raíz | Sí | `binary_tree_insert_should_satisfy_contract` / case `root` | Inserción exitosa de 50, `size == 1`, `contains(50) == true` |
| `BinaryTree`: Insertar menor y mayor | Sí | `binary_tree_insert_should_satisfy_contract` / case `lower_higher` | Inserta 50, 30, 70; `size == 3` y pertenencia de todos |
| `BinaryTree`: Ramas de varios niveles | Sí | `binary_tree_insert_should_satisfy_contract` / case `multilevel` | Inserta 50, 30, 70, 20, 40; `size == 5` |
| `BinaryTree`: Valor ausente en árbol no vacío | Sí | `binary_tree_contains_should_satisfy_contract` / case `missing_value` | Consulta 99 devuelve `false`; tamaño se mantiene |
| `BinaryTree`: Duplicado idempotente | Sí | `binary_tree_insert_should_satisfy_contract` / case `duplicate_value` | Inserta 50, 30, 70, 30; `size == 3` |
| `BinaryTree`: Inserciones ordenadas | Sí | `binary_tree_insert_should_satisfy_contract` / case `ordered_insertions` | Inserta 20, 30, 40, 50, 70; `size == 5`, 99 ausente |
| `Graph`: Crear vacío | Sí | `graph_init_should_satisfy_contract` / case `empty_graph` | `is_empty == true`, contadores en 0, consultas fallan |
| `Graph`: Vértice aislado | Sí | `graph_add_vertex_should_satisfy_contract` / case `isolated_vertex` | Añade 10; 1 vértice, 0 aristas, vecinos vacíos |
| `Graph`: Etiquetas no consecutivas y arista dirigida | Sí | `graph_add_edge_should_satisfy_contract` / case `directed_edge` | Arista (10, 70); existe hacia adelante, no en reversa |
| `Graph`: Vértice duplicado conserva adyacencia | Sí | `graph_add_vertex_should_satisfy_contract` / case `duplicate_vertex` | Re-añadir 10 preserva adyacencia `[30]` |
| `Graph`: Arista duplicada | Sí | `graph_add_edge_should_satisfy_contract` / case `duplicate_edge` | Duplicar arista (10, 30) es idempotente; 1 arista |
| `Graph`: Extremo inexistente sin mutación | Sí | `graph_add_edge_should_satisfy_contract` / case `missing_endpoint` | Intentar aristas con 98/99 falla y no muta el grafo |
| `Graph`: Vecinos ordenados y contadores | Sí | `graph_get_neighbors_should_satisfy_contract` / case `sorted_neighbors` | Vecinos devueltos en orden `[30, 50, 70]`; 4 vértices, 4 aristas |
| `Graph`: Consulta de arista ausente | Sí | `graph_has_edge_should_satisfy_contract` / case `missing_edge` | Consulta (10, 30) sin registrar arista da `false` |
| `Graph`: Vecinos de vértice inexistente | Sí | `graph_get_neighbors_should_satisfy_contract` / case `missing_neighbors` | Consultar vecinos de 99 falla con `-1` |
| `Graph`: Bucle y duplicado | Sí | `graph_add_edge_should_satisfy_contract` / case `self_loop` | Bucle (10, 10) soportado e idempotente |
| `Graph`: Aislamiento del resultado de vecinos | Sí | `graph_get_neighbors_should_satisfy_contract` / case `neighbor_isolation` | Modificar array retornado no afecta consultas posteriores |

---

## ⚠️ Limitaciones conocidas / Known limitations

| Limitación / Limitation | Impacto / Impact | Alternativa o plan / Workaround or plan |
|---|---|---|
| Liberación manual requerida para `graph_get_neighbors` | El llamador es responsable de invocar `free(*neighbors)` cuando hay vecinos | Documentado en la API del header; comportamiento estándar e idiomático en C |
| Árbol binario no auto-balanceado | Las inserciones ordenadas degeneran en lista enlazada (`O(n)`) | Conforme a la especificación de ABB básico; los árboles auto-balanceados corresponden a fases posteriores |

---

## 📝 Notas de implementación / Implementation Notes

- **Gestión de memoria:** Se proporcionan `binary_tree_free` y `graph_free` para liberar limpiamente todos los nodos asignados dinámicamente con `malloc`.
- **Aislamiento de adyacencia:** `graph_get_neighbors` asigna un buffer contiguo nuevo e independiente (`int*`) con los valores ordenados de los vecinos. Si el vértice tiene 0 vecinos, devuelve `*neighbors = NULL`, `*count = 0` y estado `0`. Si el vértice no existe, devuelve `-1` y preserva inalterados los argumentos pasados.
- **Suite de pruebas parametrizada:** En `test/data_structures_advanced_test.c`, cada operación pública (`OPERATION_TEST`) ejecuta los casos parametrizados de su abstracción de forma aislada en Criterion, totalizando 153 pruebas ejecutadas exitosamente.

**ES:** Este proyecto también está implementado en otros lenguajes. Explora el repositorio principal para consultar las demás versiones.

**EN:** This project is also implemented in other languages. Explore the main repository to see the other versions.

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
| Especificación / Specification | [`07_Data_Structures_Advanced.md`](../../../../docs/core/algorithms/07_Data_Structures_Advanced.md) |
| Primera base del lenguaje / First language reference | `data_structures_basics` — [`data_structures_basics/README.md`](../data_structures_basics/README.md) |
| Segunda base del lenguaje / Second language reference | `numbers` — [`numbers/README.md`](../../foundations/numbers/README.md) |
| Guía de inicialización / Initialisation guide | [`core/00_Project_Initialization_Guide.md`](../../../../docs/core/00_Project_Initialization_Guide.md) |
| Adaptaciones idiomáticas / Idiomatic adaptations | [`AGENT_Template.md`](../../../../docs/AGENT_Template.md) |
| Validación de la documentación / Documentation validation | [`WORKFLOW.md`](../../../../docs/WORKFLOW.md) |
| Documentación oficial del lenguaje / Language official docs | [ISO/IEC 9899:1999 (C99 Standard)](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf) |

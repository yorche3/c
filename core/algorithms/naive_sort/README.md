# Naive Sort — C

Implementación de la especificación [05_Naive_Sort](https://yorche3.github.io/programming_languages/core/algorithms/05_Naive_Sort/) en **C99**, compilada con **GCC** y probada con **Criterion**.

Biblioteca con header público en `include/`, implementación en `src/` y pruebas unitarias en `test/`.

Implementation of the [05_Naive_Sort](https://yorche3.github.io/programming_languages/core/algorithms/05_Naive_Sort/) specification in **C99**, compiled with **GCC** and tested with **Criterion**.

Library with a public header in `include/`, implementation in `src/`, and unit tests in `test/`.

---

## 📂 Archivos y estructura / Files & Structure

### Raíz del proyecto / Project root

| Archivo / File | Propósito / Purpose |
|----------------|---------------------|
| [`include/naive_sort.h`](include/naive_sort.h) | Header — declara las 3 funciones públicas / declares the 3 public functions |
| [`src/naive_sort.c`](src/naive_sort.c) | Implementación — los 3 algoritmos, cada uno con su contrato documentado |
| [`Makefile`](Makefile) | Automatización de compilación y tests / build and test automation |
| [`.gitignore`](.gitignore) | Ignora `obj/` y `bin/` / ignores `obj/` and `bin/` |

### Pruebas / Tests (`test/`)

| Archivo / File | Propósito / Purpose |
|----------------|---------------------|
| [`test/naive_sort_test.c`](test/naive_sort_test.c) | Suite Criterion: 3 tests que comparten un único motor de casos |

**Estructura de directorios / Directory structure:**

```text
naive_sort/
├── include/
│   └── naive_sort.h             # Header — 3 funciones públicas
├── src/
│   └── naive_sort.c             # Implementación — los 3 algoritmos
├── test/
│   └── naive_sort_test.c        # Suite Criterion — 3 tests
├── Makefile                     # Automatización de compilación
├── .gitignore                   # Ignora obj/, bin/
├── obj/                         # Objetos compilados (generado)
├── bin/                         # Ejecutable de tests (generado)
└── README.md                    # Este archivo
```

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** Mismo patrón de biblioteca que [`numbers`](../../foundations/numbers/README.md): un header público, una implementación y tests en `test/` descubiertos automáticamente por Criterion. La diferencia es que aquí los datos son **arrays**, no enteros sueltos, así que las pruebas comparan arrays y protegen los fixtures compartidos.

**EN:** Same library pattern as [`numbers`](../../foundations/numbers/README.md): a public header, an implementation, and tests in `test/` automatically discovered by Criterion. The difference is that the data here are **arrays**, not single integers, so the tests compare arrays and protect the shared fixtures.

### Convención de las funciones / Function contract

```c
int *selection_sort(int *arr, size_t n);
int *bubble_sort(int *arr, size_t n);
int *insertion_sort(int *arr, size_t n);
```

- `arr == NULL` → retorna `NULL`, el indicador de fallo de C / returns `NULL`, C's failure indicator.
- `n == 0` → retorna el mismo array, sin cambios / returns the same array, unchanged.
- En cualquier otro caso → ordena **in-place** y retorna `arr` / otherwise sorts **in place** and returns `arr`.

**ES:** Cada función documenta este contrato en un comentario de 3 líneas sobre su definición en `src/naive_sort.c`, siguiendo la convención de documentación del repositorio. El header se mantiene mínimo, solo con las declaraciones.

**EN:** Each function documents this contract in a 3-line comment above its definition in `src/naive_sort.c`, following the repository's documentation convention. The header stays minimal, with declarations only.

---

## 📄 Configuración clave / Key Configuration

### `include/naive_sort.h` — Header público

```c
#ifndef NAIVE_SORT_H
#define NAIVE_SORT_H

#include <stddef.h>

int *selection_sort(int *arr, size_t n);
int *bubble_sort(int *arr, size_t n);
int *insertion_sort(int *arr, size_t n);

#endif /* NAIVE_SORT_H */
```

**ES:** `<stddef.h>` aporta `size_t`; el header no incluye `<stdbool.h>` porque el `bool` de la bandera `swapped` es un detalle interno de `naive_sort.c`.

**EN:** `<stddef.h>` provides `size_t`; the header does not include `<stdbool.h>` because the `bool` for the `swapped` flag is an internal detail of `naive_sort.c`.

### `Makefile`

| Variable / Variable | Valor / Value |
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
gcc -Wall -Wextra -std=c99 -Iinclude -c -o obj/naive_sort.o src/naive_sort.c
gcc -Wall -Wextra -std=c99 -Iinclude -c -o obj/naive_sort_test.o test/naive_sort_test.c
gcc -Wall -Wextra -std=c99 -Iinclude -o bin/run_tests obj/naive_sort.o obj/naive_sort_test.o -pthread -DBXF_STATIC_LIB=1 -lcriterion
./bin/run_tests
[====] Synthesis: Tested: 3 | Passing: 3 | Failing: 0 | Crashing: 0
```

> **ES:** La compilación no emite warnings con `-Wall -Wextra -std=c99`.
> **EN:** The build emits no warnings with `-Wall -Wextra -std=c99`.

---

## 🧠 Algoritmos / Algorithms

| Algoritmo / Algorithm | Estrategia / Strategy | Complejidad temporal / Time complexity | In-place |
|---|---|---|:---:|
| `selection_sort` | Busca el mínimo del resto no ordenado y lo ubica al inicio / Finds the minimum of the unsorted remainder and places it at the front | $O(n^2)$ siempre / always | ✅ |
| `bubble_sort` | Compara e intercambia adyacentes; corta antes con la bandera `swapped` / Compares and swaps adjacent elements; exits early with the `swapped` flag | $O(n^2)$ peor/promedio, $O(n)$ mejor / worst-average, best | ✅ |
| `insertion_sort` | Construye el sub-array ordenado insertando cada elemento en su posición / Builds the sorted sub-array by inserting each element into place | $O(n^2)$ peor/promedio, $O(n)$ mejor / worst-average, best | ✅ |

### Casos cubiertos por las pruebas / Cases covered by the tests

Cada algoritmo verifica los mismos 8 casos (24 aserciones en total) / Each algorithm checks the same 8 cases (24 assertions total):

| Caso / Case | Entrada / Input | Salida esperada / Expected output |
|---|---|---|
| Desordenado / Unsorted | `{5, 2, 9, 1, 5, 6}` | `{1, 2, 5, 5, 6, 9}` |
| Ya ordenado / Already sorted | `{1, 2, 3, 4, 5}` | `{1, 2, 3, 4, 5}` |
| Orden inverso / Reverse order | `{5, 4, 3, 2, 1}` | `{1, 2, 3, 4, 5}` |
| Idénticos / Identical | `{7, 7, 7, 7}` | `{7, 7, 7, 7}` |
| Negativos / Negatives | `{3, -1, 4, -5, 0}` | `{-5, -1, 0, 3, 4}` |
| Un elemento / Single element | `{42}` | `{42}` |
| Vacío / Empty | `n = 0` | mismo puntero, sin cambios / same pointer, unchanged |
| Nulo / NULL | `arr = NULL` | `NULL` (indicador de fallo / failure indicator) |

---

## 📝 Notas de implementación / Implementation Notes

### 🧮 Ordenamiento in-place / In-place sorting

**ES:** La especificación admite ordenar in-place o devolver una copia "según el paradigma del lenguaje". En C el paradigma es in-place, así que las tres funciones mutan el buffer recibido y retornan el mismo puntero. Esto evita una API con `malloc` que obligaría al llamador a liberar memoria y crearía un contrato de propiedad inconsistente en el caso vacío.

**EN:** The specification allows sorting in place or returning a copy "depending on the language paradigm". In C the paradigm is in place, so all three functions mutate the received buffer and return the same pointer. This avoids a `malloc`-based API that would force the caller to free memory and create an inconsistent ownership contract in the empty case.

### 🧪 Estructura de las pruebas / Test structure

**ES:** Las tres funciones comparten el mismo perfil `int *(*)(int *, size_t)`, así que la suite las pasa a un único motor de casos y evita duplicar los 8 casos. Cada test es de 3 líneas:

**EN:** All three functions share the same `int *(*)(int *, size_t)` profile, so the suite passes them to a single case engine and avoids duplicating the 8 cases. Each test is 3 lines:

```c
Test(naive_sort, selection_sort)
{
    assert_all_cases(selection_sort, "selection_sort");
}
```

**ES:** `run_case()` copia la entrada a un buffer `scratch` con `memcpy` antes de llamar a la función. Es necesario porque los fixtures son `const` y compartidos entre los tres algoritmos: sin esa copia, un ordenamiento in-place los dejaría ordenados y los tests siguientes compararían sobre datos ya ordenados, dejando de ser significativos.

**EN:** `run_case()` copies the input into a `scratch` buffer with `memcpy` before calling the function. This is required because the fixtures are `const` and shared across the three algorithms: without that copy, an in-place sort would leave them sorted and the following tests would compare already-sorted data, no longer being meaningful.

### 🔁 Salida temprana en Bubble Sort / Early exit in Bubble Sort

**ES:** `bubble_sort` corta el bucle externo en cuanto una pasada no produce intercambios, cumpliendo el criterio de aceptación de la especificación.

**EN:** `bubble_sort` exits the outer loop as soon as a pass produces no swaps, satisfying the specification's acceptance criterion.

### 🛡️ `size_t` sin desbordamiento / `size_t` without underflow

**ES:** Los bucles usan `size_t`, que no admite negativos. Por eso cada función retorna antes cuando `n <= 1`; a partir de ahí `n >= 2` y expresiones como `n - 1` o `n - 1 - i` nunca pueden desbordar. En `insertion_sort`, el índice `j` también es `size_t` y el bucle usa `j > 0`, evitando la comparación `j >= 0` que en un tipo sin signo sería siempre verdadera.

**EN:** The loops use `size_t`, which cannot be negative. That is why each function returns early when `n <= 1`; from there `n >= 2` and expressions like `n - 1` or `n - 1 - i` can never underflow. In `insertion_sort`, index `j` is also `size_t` and the loop uses `j > 0`, avoiding the `j >= 0` comparison that would always be true for an unsigned type.

### ⚠️ Indicador de fallo / Failure indicator

**ES:** El contrato define `NULL` como indicador de fallo cuando `arr` es nulo. Es la representación idiomática de C: el lenguaje ya usa `NULL` para "sin valor", y la comprobación es explícita al inicio de cada función, antes de tocar el buffer. No se lanza ninguna excepción ni se señaliza error por `errno`.

**EN:** The contract defines `NULL` as the failure indicator when `arr` is null. This is C's idiomatic representation: the language already uses `NULL` for "no value", and the check is explicit at the start of each function, before touching the buffer. No exception is thrown and no error is signalled through `errno`.

---

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

This project is also implemented in other languages. Explore the [main repository](https://github.com/yorche3/programming_languages) to see all the versions.

---

*[← Volver al Roadmap](https://yorche3.github.io/programming_languages/ROADMAP/)*

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*

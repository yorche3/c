# Numbers — C

Implementación de la especificación [04_Numbers](https://yorche3.github.io/programming_languages/core/foundations/04_Numbers/) en **C99**, compilada con **GCC** y probada con **Criterion**.

Tres enfoques de implementación para los mismos 5 algoritmos: **recursivo directo**, **recursivo con acumulador** e **iterativo**.

> **ES:** C no tiene optimización de Tail Call (TCO), por lo que las funciones con acumulador (`Acc`) son puramente educativas — permiten ver cómo se implementan **helpers** (funciones auxiliares no declaradas en el header).
> **EN:** C does not have Tail Call Optimization (TCO), so accumulator-based functions (`Acc`) are purely educational — they show how **helpers** (auxiliary functions not declared in the header) are implemented.

---

## 📂 Archivos / Files

### Raíz del proyecto / Project root

| Archivo | Propósito |
|---------|-----------|
| [`include/numbers.h`](include/numbers.h) | Header — declara las 15 funciones públicas (5 algoritmos × 3 enfoques). |
| [`src/numbers.c`](src/numbers.c) | Implementación — 15 funciones más 4 helpers internos (`static`). |
| [`Makefile`](Makefile) | Automatización de compilación y tests. |
| [`.gitignore`](.gitignore) | Ignora `obj/`, `bin/` y archivos objeto. |
| [`README.md`](README.md) | Este archivo. |

### Pruebas / Tests (`test/`)

| Archivo | Propósito |
|---------|-----------|
| `test/numbers_rec_test.c` | 5 tests para el enfoque recursivo directo |
| `test/numbers_ite_test.c` | 5 tests para el enfoque iterativo |

> **ES:** No hay tests separados para el enfoque con acumulador porque:
> 1. C no tiene TCO — el consumo de pila es el mismo que la recursión directa.
> 2. Las funciones `Acc` se prueban **implícitamente** al ser llamadas desde las funciones públicas (ej: `factorial_acc(5)` llama al helper `factorial_acc_help`).
> 3. Los helpers (`_help`) son `static` y no están declarados en el header — son detalles internos de implementación.
>
> **EN:** There are no separate tests for the accumulator approach because:
> 1. C lacks TCO — stack usage is the same as direct recursion.
> 2. `Acc` functions are **implicitly tested** when called from public functions (e.g., `factorial_acc(5)` calls the helper `factorial_acc_help`).
> 3. Helpers (`_help`) are `static` and not declared in the header — they are internal implementation details.

---

## 🏗️ Enfoque / Approach

**ES:** Sigue el mismo patrón que [`calculator`](../unit_test/calculator/): un header público, una implementación y tests en `test/` descubiertos automáticamente por Criterion.

Las 15 funciones se organizan en 3 grupos por enfoque:

| Enfoque | Prefijo | Ejemplo |
|---------|---------|--------|
| Recursivo directo | `_rec` | `fibonacci_rec(n)` |
| Recursivo con acumulador | `_acc` | `fibonacci_acc(n)` |
| Iterativo | `_iter` | `fibonacci_iter(n)` |

**EN:** Follows the same pattern as [`calculator`](../unit_test/calculator/): a public header, an implementation, and tests in `test/` automatically discovered by Criterion.

The 15 functions are organized into 3 groups by approach:

| Approach | Prefix | Example |
|----------|--------|--------|
| Direct recursion | `_rec` | `fibonacci_rec(n)` |
| Accumulator recursion | `_acc` | `fibonacci_acc(n)` |
| Iterative | `_iter` | `fibonacci_iter(n)` |

---

## 📄 Archivos clave / Key Files

### `include/numbers.h` — Header público

**ES:** Declara las 15 funciones. Los helpers (`_help`) no aparecen aquí porque son `static` en `numbers.c`.

**EN:** Declares the 15 public functions. Helpers (`_help`) are not here because they are `static` in `numbers.c`.

```c
#ifndef NUMBERS_ITERATIVE_H
#define NUMBERS_ITERATIVE_H

int sum_of_first_n_rec(int n);
int factorial_rec(int n);
int fibonacci_rec(int n);
int greatest_common_divisor_rec(int a, int b);
int least_common_multiple_rec(int a, int b);

int sum_of_first_n_acc(int n);
int factorial_acc(int n);
int fibonacci_acc(int n);
int greatest_common_divisor_acc(int a, int b);
int least_common_multiple_acc(int a, int b);

int sum_of_first_n_iter(int n);
int factorial_iter(int n);
int fibonacci_iter(int n);
int greatest_common_divisor_iter(int a, int b);
int least_common_multiple_iter(int a, int b);

#endif // NUMBERS_ITERATIVE_H
```

### `src/numbers.c` — Implementación

**ES:** Cada algoritmo tiene 3 implementaciones. Los helpers `_help` son `static` (visibles solo en esta unidad de compilación). Por ejemplo, `fibonacci`:

**EN:** Each algorithm has 3 implementations. `_help` helpers are `static` (visible only in this compilation unit). For example, `fibonacci`:

```c
// Enfoque recursivo directo / Direct recursion
int fibonacci_rec(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

// Helper interno con acumulador (static, no está en el header)
// Internal accumulator helper (static, not in the header)
static int fibonacci_acc_help(int n, int a, int b) {
    if (n == 0) {
        return a;
    }
    return fibonacci_acc_help(n - 1, b, a + b);
}

// Enfoque con acumulador / Accumulator recursion
int fibonacci_acc(int n) {
    return fibonacci_acc_help(n, 0, 1);
}

// Enfoque iterativo / Iterative
int fibonacci_iter(int n) {
    if (n <= 1) {
        return n;
    }
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
```

> **ES:** Los 4 helpers (`sum_of_first_n_acc_help`, `factorial_acc_help`, `fibonacci_acc_help`, `greatest_common_divisor_acc_help`) son `static` porque:
> - No necesitan ser visibles fuera de `numbers.c`.
> - Son detalles internos de las funciones `_acc` que los llaman.
> - En C, `static` en una función limita su alcance al archivo actual.
>
> **EN:** The 4 helpers (`sum_of_first_n_acc_help`, `factorial_acc_help`, `fibonacci_acc_help`, `greatest_common_divisor_acc_help`) are `static` because:
> - They don't need to be visible outside `numbers.c`.
> - They are internal details of the `_acc` functions that call them.
> - In C, `static` on a function limits its scope to the current file.

### `test/numbers_rec_test.c` — Pruebas recursivas

**ES:** Cada grupo `Test(numbers_rec, ...)` contiene aserciones con `cr_expect_eq`.

**EN:** Each `Test(numbers_rec, ...)` group contains assertions with `cr_expect_eq`.

```c
#include <criterion/criterion.h>
#include "../include/numbers.h"

Test(numbers_rec, sum_of_first_n_rec) {
    cr_expect_eq(sum_of_first_n_rec(0), 0);
    cr_expect_eq(sum_of_first_n_rec(3), 6);
}

Test(numbers_rec, fibonacci_rec) {
    cr_expect_eq(fibonacci_rec(0), 0);
    cr_expect_eq(fibonacci_rec(1), 1);
    cr_expect_eq(fibonacci_rec(6), 8);
}
```

### `test/numbers_ite_test.c` — Pruebas iterativas

**ES:** Misma estructura que las recursivas, pero probando las funciones `_iter`.

**EN:** Same structure as the recursive ones, but testing the `_iter` functions.

```c
#include <criterion/criterion.h>
#include "../include/numbers.h"

Test(numbers_ite, sum_of_first_n_iter) {
    cr_expect_eq(sum_of_first_n_iter(0), 0);
    cr_expect_eq(sum_of_first_n_iter(3), 6);
}

Test(numbers_ite, fibonacci_iter) {
    cr_expect_eq(fibonacci_iter(0), 0);
    cr_expect_eq(fibonacci_iter(1), 1);
    cr_expect_eq(fibonacci_iter(6), 8);
}
```

---

## 🚀 Compilar y ejecutar / Build & Run

### Requisito: Tener GCC, make y Criterion instalados

```bash
# Linux (Debian/Ubuntu)
sudo apt install gcc make libcriterion-dev
```

### Ejecutar pruebas unitarias

```bash
make test    # Compila y ejecuta tests (10 tests)
make clean   # Limpia obj/ y bin/
```

**Salida esperada / Expected output:**

```text
[====] Synthesis: Tested: 10 | Passing: 10 | Failing: 0
```

> **ES:** 10 tests en total (5 recursivos + 5 iterativos). Los acumuladores se prueban implícitamente al ser invocados desde las funciones `_acc`.
> **EN:** 10 tests total (5 recursive + 5 iterative). Accumulators are implicitly tested as they are called by the `_acc` functions.

---

## 📁 Estructura / Structure

```text
numbers/
├── include/
│   └── numbers.h                # Header — 15 funciones públicas
├── src/
│   └── numbers.c                # Implementación — 15 funciones + 4 helpers static
├── test/
│   ├── numbers_rec_test.c       # Tests recursivos (5)
│   └── numbers_ite_test.c       # Tests iterativos (5)
├── Makefile                     # Automatización de compilación
├── .gitignore                   # Ignora obj/, bin/
├── obj/                         # Objetos compilados (generado)
├── bin/                         # Ejecutable de tests (generado)
└── README.md                    # Este archivo
```

---

## 🧪 Algoritmos / Algorithms

### 3 enfoques × 5 algoritmos = 15 funciones / 10 tests

| Algoritmo | Casos de prueba | `_rec` | `_acc` | `_iter` |
|-----------|----------------|:------:|:------:|:-------:|
| `sum_of_first_n` | `(0) = 0`, `(3) = 6` | ✅ | ✅¹ | ✅ |
| `factorial` | `(0) = 1`, `(4) = 24` | ✅ | ✅¹ | ✅ |
| `fibonacci` | `(0) = 0`, `(1) = 1`, `(6) = 8` | ✅ | ✅¹ | ✅ |
| `greatest_common_divisor` | `(12, 8) = 4`, `(7, 5) = 1` | ✅ | ✅¹ | ✅ |
| `least_common_multiple` | `(4, 6) = 12`, `(6, 8) = 24` | ✅ | ✅¹ | ✅ |

> ¹ Los acumuladores se prueban implícitamente al ejecutar `_acc(n)`, que internamente llama al helper `static`. No tienen tests directos porque son detalles de implementación.
> ¹ Accumulators are implicitly tested when `_acc(n)` runs, which internally calls the `static` helper. They have no direct tests because they are implementation details.

---

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

## 📝 Notas / Notes

- **ES:** C no tiene TCO (Tail Call Optimization), por lo que las funciones con acumulador (`_acc`) consumen la misma pila que las recursivas directas. Se incluyen por coherencia educativa con las implementaciones en otros lenguajes del repositorio.
- **EN:** C lacks TCO (Tail Call Optimization), so accumulator-based functions (`_acc`) consume the same stack as direct recursion. They are included for educational consistency with implementations in other languages in the repository.
- **ES:** Los helpers `_help` son funciones `static` no declaradas en el header. Esta es una práctica común en C para encapsular lógica auxiliar: se mantienen en el `.c` y no forman parte de la API pública.
- **EN:** The `_help` helpers are `static` functions not declared in the header. This is a common C practice to encapsulate auxiliary logic: they stay in the `.c` and are not part of the public API.
- **ES:** C99 no permite declaraciones `int i = 0` dentro del `for` si se compila con `-std=c99` estricto. El código usa esta característica porque GCC la soporta incluso en C99 (es una extensión aceptada).
- **EN:** C99 does not allow `int i = 0` declarations inside `for` if compiled with strict `-std=c99`. The code uses this feature because GCC supports it even in C99 (it's an accepted extension).

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*

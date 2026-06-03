# Calculator — C

Implementación de la especificación [03_Unit_Test_Calculator](https://yorche3.github.io/programming_languages/core/foundations/03_Unit_Test_Calculator/) en **C99**, usando **Criterion** como framework de pruebas unitarias.

---

## 📂 Archivos / Files

### Raíz del proyecto / Project root

| Archivo | Propósito |
|---------|-----------|
| [`include/calculator.h`](include/calculator.h) | Header — declara las 5 operaciones aritméticas. |
| [`src/calculator.c`](src/calculator.c) | Implementación — suma repetitiva para multiplicación, resta repetitiva para división. |
| [`Makefile`](Makefile) | Automatización de compilación y tests (`make`, `make test`, `make clean`). |
| [`.gitignore`](.gitignore) | Ignora `obj/`, `bin/` y archivos objeto. |
| [`README.md`](README.md) | Este archivo. |

### Pruebas / Tests (`test/`)

| Archivo | Propósito |
|---------|-----------|
| `test/calculator_test.c` | Pruebas unitarias — 5 grupos con 3 aserciones cada uno, usando el macro `Test()` de Criterion. |

> **ES:** Criterion genera su propio `main()` automáticamente, por lo que no se necesita un archivo `run_tests.c`.
> **EN:** Criterion generates its own `main()` automatically, so no `run_tests.c` file is needed.

---

## 🏗️ Enfoque / Approach

**ES:** Este proyecto usa el framework de pruebas **Criterion**, que:

1. Descubre automáticamente los tests gracias al macro `Test(suite, nombre)`.
2. Soporta aserciones como `cr_expect_eq(actual, esperado)` y `cr_assert_eq`.
3. No requiere punto de entrada manual — Criterion inyecta su propio `main`.
4. Se integra vía `pkg-config` para flags de compilación y enlace.

**EN:** This project uses the **Criterion** test framework, which:

1. Automatically discovers tests via the `Test(suite, name)` macro.
2. Supports assertions like `cr_expect_eq(actual, expected)` and `cr_assert_eq`.
3. No manual entry point needed — Criterion injects its own `main`.
4. Integrates via `pkg-config` for compilation and linking flags.

---

## 📄 Archivos clave / Key Files

### `include/calculator.h` — Header

**ES:** Declara los prototipos de las 5 funciones públicas.

**EN:** Declares the prototypes for the 5 public functions.

```c
#ifndef CALCULATOR_H
#define CALCULATOR_H

int addition(int a, int b);
int subtraction(int a, int b);
int multiplication(int a, int b);
int division(int a, int b);
int modulus(int a, int b);

#endif // CALCULATOR_H
```

### `src/calculator.c` — Implementación

**ES:** Contiene las 5 operaciones aritméticas. `multiplication` usa suma repetitiva (`for`), `division` usa resta repetitiva (`while`), y `modulus` se define en términos de `division` y `multiplication`, cumpliendo la especificación educativa.

**EN:** Contains the 5 arithmetic operations. `multiplication` uses repeated addition (`for`), `division` uses repeated subtraction (`while`), and `modulus` is defined in terms of `division` and `multiplication`, complying with the educational specification.

```c
#include "../include/calculator.h"

int addition(int a, int b) {
    return a + b;
}

int multiplication(int a, int b) {
    int product = 0;
    for (int i = 0; i < b; i++) {
        product = addition(product, a);
    }
    return product;
}

int division(int a, int b) {
    int quotient = 0;
    while (a >= b) {
        a -= b;
        quotient++;
    }
    return quotient;
}

int modulus(int a, int b) {
    return subtraction(a, multiplication(b, division(a, b)));
}
```

### `test/calculator_test.c` — Pruebas unitarias

**ES:** Cada grupo `Test(calculator, ...)` contiene múltiples aserciones con `cr_expect_eq`. Criterion ejecuta todos los tests automáticamente.

**EN:** Each `Test(calculator, ...)` group contains multiple assertions with `cr_expect_eq`. Criterion runs all tests automatically.

```c
#include <criterion/criterion.h>
#include "../include/calculator.h"

Test(calculator, addition) {
    cr_expect_eq(addition(2, 3), 5);
    cr_expect_eq(addition(-1, 1), 0);
    cr_expect_eq(addition(0, 0), 0);
}

Test(calculator, multiplication) {
    cr_expect_eq(multiplication(3, 4), 12);
    cr_expect_eq(multiplication(0, 5), 0);
    cr_expect_eq(multiplication(5, 0), 0);
}
```

### `Makefile`

**ES:** Compila el módulo y los tests, enlaza con Criterion vía `pkg-config`. Usa `-Iinclude` para localizar el header.

**EN:** Compiles the module and tests, links with Criterion via `pkg-config`. Uses `-Iinclude` to locate the header.

```makefile
CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS  = $(shell pkg-config --cflags --libs criterion)

SRC_DIR  = src
TEST_DIR = test
OBJ_DIR  = obj
BIN_DIR  = bin

SRC      = $(SRC_DIR)/calculator.c
TEST_SRC = $(TEST_DIR)/calculator_test.c
OBJ      = $(OBJ_DIR)/calculator.o
TEST_OBJ = $(OBJ_DIR)/calculator_test.o
TEST_BIN = $(BIN_DIR)/run_tests

.PHONY: all build test clean

all: test

build: $(OBJ_DIR) $(BIN_DIR) $(OBJ)

test: $(OBJ_DIR) $(BIN_DIR) $(TEST_BIN)
	./$(TEST_BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/calculator.o: $(SRC) include/calculator.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/calculator_test.o: $(TEST_DIR)/calculator_test.c include/calculator.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_BIN): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
```

---

## 🚀 Compilar y ejecutar / Build & Run

### Requisito: Tener GCC, make y Criterion instalados

```bash
# Linux (Debian/Ubuntu)
sudo apt install gcc make libcriterion-dev

# macOS
brew install gcc make criterion
```

### Ejecutar pruebas unitarias

```bash
make test    # Compila y ejecuta tests
make clean   # Limpia obj/ y bin/
```

**Salida esperada / Expected output:**

```text
[====] Synthesis: Tested: 5 | Passing: 5 | Failing: 0
```

> **ES:** Criterion resume los resultados al final. Los 5 grupos deben pasar (5 passing, 0 failing).
> **EN:** Criterion summarizes results at the end. All 5 groups must pass (5 passing, 0 failing).

---

## 📁 Estructura / Structure

```text
calculator/
├── include/
│   └── calculator.h         # Header — prototipos de las funciones
├── src/
│   └── calculator.c         # Implementación — 5 operaciones aritméticas
├── test/
│   └── calculator_test.c    # Pruebas unitarias (5 grupos)
├── Makefile                 # Automatización de compilación
├── .gitignore               # Ignora obj/, bin/ y archivos objeto
├── obj/                     # Objetos compilados (generado)
├── bin/                     # Ejecutable de tests (generado)
└── README.md                # Este archivo
```

---

## 🧪 Operaciones / Operations

| Función | Implementación | Cumple |
|---------|---------------|--------|
| `addition(a, b)` | `a + b` (suma directa) | ✅ |
| `subtraction(a, b)` | `a - b` (resta directa) | ✅ |
| `multiplication(a, b)` | Suma repetitiva de `a`, `b` veces con `for` | ✅ No usa `*` |
| `division(a, b)` | Resta repetitiva con `while`: cuántas veces cabe `b` en `a` | ✅ No usa `/` |
| `modulus(a, b)` | `a - multiplication(division(a, b), b)` | ✅ No usa `%` |

---

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

## 📝 Notas / Notes

- **ES:** Criterion descubre automáticamente los tests definidos con el macro `Test()`. No es necesario registrarlos manualmente.
- **EN:** Criterion automatically discovers tests defined with the `Test()` macro. No manual registration is needed.
- **ES:** Las funciones `multiplication` y `division` están implementadas con sumas/restas repetitivas para cumplir la especificación educativa (no usar operadores `*` ni `/` directos).
- **EN:** The `multiplication` and `division` functions are implemented with repeated addition/subtraction to comply with the educational specification (no direct `*` or `/` operators).

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*

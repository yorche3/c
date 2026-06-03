# 🚀 Foundations — C

Implementaciones de la [Fase 0 — Fundamentos](https://yorche3.github.io/programming_languages/ROADMAP/#fase-0--fundamentos--foundations--completada) en **C99**: `hello_world`, `hello_user`, `unit_test/calculator` y `numbers`.

---

## 📖 Módulos / Modules

| Módulo | Especificación | Enfoque | Tests | Estado |
|--------|---------------|---------|:-----:|:------:|
| [`helloworld/`](helloworld/) | [01_Hello_World](https://yorche3.github.io/programming_languages/core/foundations/01_Hello_World/) | `gcc` + `make` (archivo único) | — | ✅ |
| [`hellouser/`](hellouser/) | [02_Hello_User](https://yorche3.github.io/programming_languages/core/foundations/02_Hello_User/) | `gcc` + `make` (archivo único) | — | ✅ |
| [`unit_test/calculator/`](unit_test/calculator/) | [03_Unit_Test_Calculator](https://yorche3.github.io/programming_languages/core/foundations/03_Unit_Test_Calculator/) | `gcc` + `make` + **Criterion** | 5 | ✅ |
| [`numbers/`](numbers/) | [04_Numbers](https://yorche3.github.io/programming_languages/core/foundations/04_Numbers/) | `gcc` + `make` + **Criterion** | 10 | ✅ |

---

## 📁 Estructura / Structure

```text
foundations/
├── helloworld/                   # 01_Hello_World
│   ├── hello_world.c             # Imprime "Hello, World!"
│   ├── Makefile
│   └── README.md
│
├── hellouser/                    # 02_Hello_User
│   ├── hello_user.c              # Lee nombre y saluda
│   ├── Makefile
│   └── README.md
│
├── unit_test/
│   └── calculator/               # 03_Unit_Test_Calculator
│       ├── include/
│       │   └── calculator.h      # Header con prototipos
│       ├── src/
│       │   └── calculator.c      # 5 operaciones aritméticas
│       ├── test/
│       │   └── calculator_test.c # 5 tests con Criterion
│       ├── Makefile
│       └── README.md
│
└── numbers/                      # 04_Numbers
    ├── include/
    │   └── numbers.h             # Header con 15 prototipos
    ├── src/
    │   └── numbers.c             # 15 funciones + 4 helpers static
    ├── test/
    │   ├── numbers_rec_test.c    # 5 tests recursivos
    │   └── numbers_ite_test.c    # 5 tests iterativos
    ├── Makefile
    └── README.md
```

---

## 🛠️ Patrón común / Common Pattern

| Característica | Descripción |
|---------------|-------------|
| **Compilador** | GCC con `-Wall -Wextra -std=c99` |
| **Build system** | `make` con targets `build`, `test`, `clean` |
| **Test framework** | [Criterion](https://github.com/Snaipe/Criterion) v2.4.x |
| **Detección de tests** | Automática vía macro `Test(suite, nombre)` — Criterion inyecta su propio `main` |
| **Aserciones** | `cr_expect_eq(actual, expected)` y `cr_assert_eq(actual, expected)` |
| **Separación** | `include/` (headers), `src/` (implementación), `test/` (tests) |
| **Sin dependencias externas** | Solo `libcriterion-dev` para tests; ninguna para el código fuente |

---

## 🚀 Compilación rápida / Quick Build

```bash
# Hello, World!
cd helloworld && make run

# Hello, User!
cd hellouser && make run

# Calculator Tests
cd unit_test/calculator && make test

# Numbers Tests
cd numbers && make test
```

---

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

## ▶️ Siguiente / Next

👉 Después de fundamentos, continúa con [Fase 1 — Algoritmos Puros](https://yorche3.github.io/programming_languages/ROADMAP/#fase-1--algoritmos-puros--algorithms-pure-).  
👉 After foundations, continue with [Phase 1 — Algorithms Pure](https://yorche3.github.io/programming_languages/ROADMAP/#fase-1--algoritmos-puros--algorithms-pure-).

---

*[← Volver a C](../../README.md)*

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*

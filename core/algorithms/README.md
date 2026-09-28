# 🚀 Algorithms Pure — C

Implementaciones de la [Fase 1 — Algoritmos Puros](https://yorche3.github.io/programming_languages/ROADMAP/#fase-1--algoritmos-puros--algorithms-pure-) en **C99**: algoritmos sobre arrays con indicadores de fallo compatibles y sin excepciones.

---

## 📁 Estructura / Structure

```text
algorithms/
├── naive_sort/               # 05_Naive_Sort
│   ├── include/
│   │   └── naive_sort.h
│   ├── src/
│   │   └── naive_sort.c
│   ├── test/
│   │   └── naive_sort_test.c
│   ├── Makefile
│   └── README.md
└── data_structures_basics/   # 06_Data_Structures_Basics
    ├── include/
    │   └── data_structures_basics.h
    ├── src/
    │   └── data_structures_basics.c
    ├── test/
    │   └── data_structures_basics_test.c
    ├── Makefile
    └── README.md
```

---

## 📖 Módulos / Modules

| Módulo | Especificación | Enfoque | Tests | Estado |
|--------|---------------|---------|-------|--------|
| [`naive_sort/`](naive_sort/) | [05_Naive_Sort](https://yorche3.github.io/programming_languages/core/algorithms/05_Naive_Sort/) | `make test` (lib + Criterion) | 3 | ✅ |
| [`data_structures_basics/`](data_structures_basics/) | [06_Data_Structures_Basics](https://yorche3.github.io/programming_languages/core/algorithms/06_Data_Structures_Basics/) | `make test` (lib + Criterion) | 4 | ✅ |
| `data_structures_advanced` | [07_Data_Structures_Advanced](https://yorche3.github.io/programming_languages/core/algorithms/07_Data_Structures_Advanced/) | — | — | 📋 |
| `efficient_sort` | [08_Efficient_Sort](https://yorche3.github.io/programming_languages/core/algorithms/08_Efficient_Sort/) | — | — | 📋 |
| `distributed_sort` | [09_Distributed_Sort](https://yorche3.github.io/programming_languages/core/algorithms/09_Distributed_Sort/) | — | — | 📋 |
| `searching` | [10_Searching](https://yorche3.github.io/programming_languages/core/algorithms/10_Searching/) | — | — | 📋 |

> **ES:** `naive_sort` y `data_structures_basics` son las dos primeras implementaciones homologadas de esta fase en C. Los módulos restantes siguen el orden de la numeración canónica `07_` a `10_`.
> **EN:** `naive_sort` and `data_structures_basics` are the first two standardized implementations of this phase in C. The remaining modules follow the canonical numbering from `07_` to `10_`.

---

## 🛠️ Patrón común / Common Pattern

| Elemento | Valor |
|---|---|
| Runtime | GCC (C99) |
| Framework de pruebas / Test framework | [Criterion](https://criterion-test.readthedocs.io/en/latest/) |
| Build | `Makefile` con targets `all`, `build`, `test`, `clean` |
| Layout | `include/` (header público) + `src/` (implementación) + `test/` (suite) |
| Artefactos generados / Generated artifacts | `obj/` (objetos) + `bin/run_tests` (ejecutable de tests) |

---

## 🚀 Compilación rápida / Quick Build

```bash
# Naive Sort
cd naive_sort && make test

# Data Structures Basics
cd data_structures_basics && make test
```

---

## ▶️ Siguiente / Next

👉 Empieza por [`naive_sort`](naive_sort/README.md).
👉 Start with [`naive_sort`](naive_sort/README.md).

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*[← Volver a Core](../README.md)*

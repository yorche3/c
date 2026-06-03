# C

Proyectos en **C99**, compilados con **GCC** y probados con **Criterion**.

Usa `make` como build system y [Criterion](https://github.com/Snaipe/Criterion) como framework de pruebas unitarias.

---

## 📂 Módulos / Modules

| Módulo | Descripción |
|--------|-------------|
| [`core/foundations/`](core/foundations/) | **Fase 0 — Fundamentos**: `hello_world`, `hello_user`, `calculator`, `numbers` |

---

### ▶️ Comenzar / Getting Started

```bash
# Hello, World!
cd core/foundations/helloworld && make run

# Hello, User!
cd core/foundations/hellouser && make run

# Calculator Tests
cd core/foundations/unit_test/calculator && make test

# Numbers Tests
cd core/foundations/numbers && make test
```

---

### 📦 Requisitos / Requirements

| Herramienta | Instalación |
|-------------|-------------|
| [GCC](https://gcc.gnu.org/) | `sudo apt install gcc` (Linux) / `winget install GCC.GCC` (Windows) |
| [Make](https://www.gnu.org/software/make/) | `sudo apt install make` (Linux) |
| [Criterion](https://github.com/Snaipe/Criterion) | `sudo apt install libcriterion-dev` (Linux) |

```bash
# Verificar instalación
gcc --version && make --version && pkg-config --modversion criterion
```

---

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*
# Hello, World! — C

Implementación de la especificación [01_Hello_World](https://yorche3.github.io/programming_languages/core/foundations/01_Hello_World/) en **C99**, compilada con **GCC**.

---

## 📂 Archivos / Files

| Archivo | Propósito |
|---------|-----------|
| [`hello_world.c`](hello_world.c) | Código fuente: imprime `"Hello, World! from C!"` en la consola. |
| [`Makefile`](Makefile) | Automatización de compilación (`make`, `make run`, `make clean`). |
| [`README.md`](README.md) | Este archivo. |

---

## 🛠️ Enfoque / Approach

**ES:** Este proyecto usa **C99** con **GCC** y sigue un enfoque minimalista: un único archivo fuente, sin dependencias externas, compilado directamente con `gcc`.

Características:
- **Sin bibliotecas externas** — solo `<stdio.h>` para `printf`.
- **Estándar C99** — `-std=c99` para portabilidad.
- **Compilación directa** — un solo comando `gcc` genera el ejecutable.
- **Sin sistema de proyectos** — no se necesita CMake, Meson ni autotools.

**EN:** This project uses **C99** with **GCC** and follows a minimalist approach: a single source file, no external dependencies, compiled directly with `gcc`.

Features:
- **No external libraries** — only `<stdio.h>` for `printf`.
- **C99 standard** — `-std=c99` for portability.
- **Direct compilation** — a single `gcc` command generates the executable.
- **No build system** — no CMake, Meson or autotools needed.

---

## 📄 Archivos clave / Key Files

### `hello_world.c`

**ES:** Punto de entrada `main()`. Incluye `<stdio.h>` para `printf` y retorna `0` al sistema operativo indicando éxito.

**EN:** Entry point `main()`. Includes `<stdio.h>` for `printf` and returns `0` to the OS indicating success.

```c
#include <stdio.h>

int main()
{
  printf("Hello, World! from C!\n");
  return 0;
}
```

| Elemento | Propósito |
|----------|-----------|
| `#include <stdio.h>` | Importa la biblioteca estándar de E/S |
| `int main()` | Punto de entrada del programa |
| `printf(...)` | Imprime una cadena con formato en la salida estándar |
| `return 0;` | Código de salida: 0 = éxito |

### `Makefile`

**ES:** Compilación con GCC y flags `-Wall -Wextra` para advertencias exhaustivas y `-std=c99` para el estándar C99.

**EN:** Compilation with GCC using `-Wall -Wextra` for exhaustive warnings and `-std=c99` for the C99 standard.

```makefile
CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99
TARGET   = hello_world
SRC      = hello_world.c

.PHONY: all build run clean

all: build

build: $(TARGET)
	$(CC) $(CFLAGS) -o $@ $<

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET) hello_world.o
```

| Target | Acción |
|--------|--------|
| `make` / `make build` | Compila `hello_world.c` → `hello_world` |
| `make run` | Compila y ejecuta |
| `make clean` | Elimina binario y objeto |

---

## 🚀 Compilar y ejecutar / Build & Run

### Requisito: Tener GCC y make instalados

```bash
# Linux (Debian/Ubuntu)
sudo apt install gcc make

# macOS
xcode-select --install

# Windows
winget install GCC. GCC  # MinGW-w64 vía winget
```

### Con Makefile (recomendado)

```bash
make        # Compilar
make run    # Compilar y ejecutar
```

**Salida esperada / Expected output:**

```text
Hello, World! from C!
```

### Manualmente (sin Makefile)

```bash
gcc -Wall -Wextra -std=c99 -o hello_world hello_world.c
./hello_world
```

---

## 📁 Estructura / Structure

```text
helloworld/
├── hello_world.c    # Código fuente
├── Makefile         # Automatización de compilación
├── README.md        # Este archivo
└── hello_world      # Ejecutable (generado)
```

---

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*

# Hello, User! — C

Implementación de la especificación [02_Hello_User](https://yorche3.github.io/programming_languages/core/foundations/02_Hello_User/) en **C99**, compilada con **GCC**.

Lee un nombre desde la entrada estándar y saluda al usuario.

---

## 📂 Archivos / Files

| Archivo | Propósito |
|---------|-----------|
| [`hello_user.c`](hello_user.c) | Código fuente: solicita un nombre al usuario y saluda. |
| [`Makefile`](Makefile) | Automatización de compilación (`make`, `make run`, `make clean`). |
| [`README.md`](README.md) | Este archivo. |

---

## 🛠️ Enfoque / Approach

**ES:** Este programa introduce dos conceptos nuevos respecto a `hello_world`:

1. **Lectura de entrada** — `fgets()` lee una línea desde `stdin` con límite de tamaño para evitar desbordamiento.
2. **Procesamiento del nombre** — `strlen()` + eliminación del `\n` final que `fgets` incluye al presionar Enter.

**EN:** This program introduces two new concepts compared to `hello_world`:

1. **Input reading** — `fgets()` reads a line from `stdin` with a size limit to prevent buffer overflow.
2. **Name processing** — `strlen()` + removal of the trailing `\n` that `fgets` includes when pressing Enter.

---

## 📄 Archivos clave / Key Files

### `hello_user.c`

**ES:** El flujo del programa es:

1. Declarar un buffer `name` de 100 caracteres.
2. Imprimir `"Enter your name: "` con `printf`.
3. Leer entrada con `fgets`, que respeta el límite del buffer.
4. Calcular la longitud con `strlen` y eliminar el `\n` final si existe.
5. Imprimir `"Hello, <nombre>!"` con `printf`.
6. Retornar 0 indicando éxito.

**EN:** Program flow:

1. Declare a `name` buffer of 100 characters.
2. Print `"Enter your name: "` with `printf`.
3. Read input with `fgets`, which respects the buffer size limit.
4. Calculate length with `strlen` and remove trailing `\n` if present.
5. Print `"Hello, <name>!"` with `printf`.
6. Return 0 indicating success.

```c
#include <stdio.h>
#include <string.h>

int main()
{
  char name[100];

  printf("Enter your name: ");
  fgets(name, sizeof(name), stdin);

  // Remove newline character if present
  size_t len = strlen(name);
  if (len > 0 && name[len - 1] == '\n')
  {
    name[len - 1] = '\0';
  }

  printf("Hello, %s!\n", name);
  return 0;
}
```

| Elemento | Propósito |
|----------|-----------|
| `#include <string.h>` | Importa `strlen` para obtener la longitud de la cadena |
| `char name[100]` | Buffer de 100 caracteres para almacenar el nombre |
| `fgets(name, sizeof(name), stdin)` | Lee hasta 99 caracteres desde `stdin`, incluye el `\n` |
| `strlen(name)` | Obtiene la longitud actual de la cadena |
| `name[len - 1] = '\0'` | Reemplaza el `\n` final con el terminador nulo |

> **ES:** Se usa `fgets` en lugar de `scanf("%s", name)` para evitar desbordamiento de buffer y problemas con espacios en el nombre.
> **EN:** `fgets` is used instead of `scanf("%s", name)` to avoid buffer overflow and issues with spaces in the name.

### `Makefile`

**ES:** Idéntico al de `hello_world`, solo cambia el nombre del target. Ver [`helloworld/README.md`](../helloworld/README.md) para la explicación detallada.

**EN:** Same as `hello_world`, only the target name changes. See [`helloworld/README.md`](../helloworld/README.md) for the detailed explanation.

| Target | Acción |
|--------|--------|
| `make` / `make build` | Compila `hello_user.c` → `hello_user` |
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
winget install GCC.GCC  # MinGW-w64 vía winget
```

### Con Makefile (recomendado)

```bash
make run
```

**Salida esperada / Expected output:**

```text
Enter your name: Ada
Hello, Ada!
```

### Manualmente (sin Makefile)

```bash
gcc -Wall -Wextra -std=c99 -o hello_user hello_user.c
./hello_user
```

---

## 📁 Estructura / Structure

```text
hellouser/
├── hello_user.c    # Código fuente
├── Makefile        # Automatización de compilación
├── README.md       # Este archivo
└── hello_user      # Ejecutable (generado)
```

---

### 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*

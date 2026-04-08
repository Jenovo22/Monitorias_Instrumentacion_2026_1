# Tutorial básico de GitHub para los laboratorios (ESP32 + Arduino IDE)

## 1. ¿Qué es Git y qué es GitHub?

**Git** es un sistema de control de versiones. Permite registrar los cambios que se realizan en un proyecto y conservar un historial de versiones.

**GitHub** es una plataforma en línea donde se almacenan repositorios Git. Permite:

* Guardar código en la nube
* Mantener historial de cambios
* Compartir proyectos
* Entregar evidencias de trabajo

En este curso usaremos GitHub para:

* Subir el código desarrollado en los laboratorios
* Mantener registro de los cambios realizados
* Tener un repositorio que sirva como evidencia del trabajo realizado

---

# 2. Conceptos básicos

## Repositorio

Un **repositorio** es la carpeta del proyecto que se almacena en GitHub.

## Fork

Un **Fork** es crear una copia exacta de un repositorio ajeno en tu propia cuenta. Esto te permite editar el proyecto y subir tus propios cambios sin afectar el original.

## Commit

Un **commit** es un registro de cambios en el proyecto. Cada commit incluye los archivos modificados y un mensaje explicando qué se cambió.

## Push

**Push** significa **subir los cambios al repositorio en GitHub** (Computador → GitHub).

## Pull

**Pull** significa **descargar cambios desde GitHub al computador** (GitHub → Computador).

## Branch (rama)

Una **rama** es una versión paralela del proyecto. Para los laboratorios normalmente se trabajará únicamente en la rama: `main`.

---

# 3. Instalación de herramientas

Para este curso se utilizarán:

* **Arduino IDE**
* **GitHub Desktop** (Herramienta principal)
* **GitHub**
* **Git Bash** (Opcional - para comandos de consola)

---

## Paso 1 — Crear cuenta en GitHub

Ir a: `https://github.com` y crear una cuenta personal.

---

## Paso 2 — Instalar GitHub Desktop

Descargar desde: `https://desktop.github.com`. Instalar e iniciar sesión. Permite usar Git de forma visual sin necesidad de usar la terminal.

---

# 4. Crear su propio repositorio para los laboratorios

## Paso 1 — Realizar un Fork (Si el monitor provee una base)
Si el monitor indica un repositorio base, presiona el botón **Fork** en la parte superior derecha de la página de GitHub para tener tu propia copia.

## Paso 2 — Crear un repositorio nuevo
Si empiezas desde cero, en GitHub selecciona `New repository`. 
* Nombre: `laboratorios-esp32`
* Opción: Activar **Add README**

---

# 5. Descargar el repositorio al computador

Abrir **GitHub Desktop**.
1. Ir a: `File → Clone repository`.
2. Seleccionar su repositorio.
3. Elegir la carpeta local (Ejemplo: `Documentos/laboratorios-esp32/`).

---

# 6. Organización recomendada del repositorio

Se recomienda crear una carpeta por cada laboratorio o punto:
```
laboratorios-esp32/
   laboratorio1/
      led_blink.ino
   laboratorio2/
      sensor_ultrasonico.ino
```

---

# 7. Editar el código con Arduino IDE

1. Abrir el archivo `.ino` desde la carpeta del repositorio.
2. Realizar los cambios necesarios.
3. **Guardar siempre los archivos** antes de volver a GitHub Desktop.

---

# 8. Subir el laboratorio a GitHub (Flujo Principal)

Abrir **GitHub Desktop**. El programa detectará automáticamente los cambios.

## Paso 1 — Crear un commit
En el recuadro inferior izquierdo (Summary), escribe qué hiciste. Ejemplo: `"Punto 3: Lectura de LDR funcionando"`. Seleccionar **Commit to main**.

## Paso 2 — Subir a GitHub
Presionar el botón **Push origin** en la parte superior.

---

# 9. Cómo restaurar versiones (Si algo falla)

### Caso A: Si aún no has hecho Commit
Si dañaste el código y quieres volver a como estaba al inicio:
* En GitHub Desktop, en la pestaña **Changes**, haz clic derecho sobre el archivo y selecciona **Discard Changes**.

### Caso B: Si ya hiciste Commit y Push
Si subiste algo que no funciona y quieres deshacerlo:
1. Ve a la pestaña **History**.
2. Haz clic derecho sobre el commit que quieres anular.
3. Selecciona **Revert Changes in Commit**. Esto crea un nuevo estado que "cura" el error.
4. Presiona **Push origin**.

---

# 10. Opción Extra: Comandos por Consola (Git Bash)

Si prefieres usar la terminal, abre **Git Bash** en la carpeta de tu proyecto:

| Acción | Comando |
| :--- | :--- |
| **Clonar** | `git clone [URL_DEL_REPO]` |
| **Preparar cambios** | `git add .` |
| **Guardar (Commit)** | `git commit -m "Mensaje explicativo"` |
| **Subir (Push)** | `git push origin main` |
| **Bajar (Pull)** | `git pull origin main` |
| **Restaurar archivo** | `git restore [archivo.ino]` |
| **Ver historial** | `git log --oneline` |
| **Resetear al pasado** | `git reset --hard [ID_DEL_COMMIT]` |

---

# 11. Recursos de instalación

* Instalación y uso básico de Git y GitHub: [https://www.youtube.com/watch?v=cae7EFzd02M](https://www.youtube.com/watch?v=cae7EFzd02M)
* Introducción a GitHub y flujo básico: [https://www.youtube.com/watch?v=r4ynZyLuf-o](https://www.youtube.com/watch?v=r4ynZyLuf-o)

# Herramientas utilizadas

* Arduino IDE
* GitHub
* GitHub Desktop
* Git Bash
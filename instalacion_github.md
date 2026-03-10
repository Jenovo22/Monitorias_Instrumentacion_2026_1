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

Ejemplo de estructura:

```
Laboratorios-ESP32/
   laboratorio1/
      led_blink.ino
   laboratorio2/
      sensor_ultrasonico.ino
   README.md
```

Todo lo que esté dentro del repositorio puede almacenarse en GitHub.

---

## Commit

Un **commit** es un registro de cambios en el proyecto.

Cada commit incluye:

* Los archivos modificados
* Un mensaje explicando qué se cambió

Ejemplo:

```
Commit: "Se agregó lectura del sensor DHT11"
```

---

## Push

**Push** significa **subir los cambios al repositorio en GitHub**.

Dirección:

```
computador → GitHub
```

Después de realizar cambios en el código:

```
commit → push
```

---

## Pull

**Pull** significa **descargar cambios desde GitHub al computador**.

Dirección:

```
GitHub → computador
```

Se usa cuando el repositorio tiene cambios que aún no están en el computador.

---

## Branch (rama)

Una **rama** es una versión paralela del proyecto que permite trabajar sin afectar la versión principal.

Ejemplo:

```
main
wifi-test
sensor-development
```

Para los laboratorios normalmente se trabajará únicamente en:

```
main
```

---

# 3. Instalación de herramientas

Para este curso se utilizarán:

* **Arduino IDE**
* **GitHub Desktop**
* **GitHub**

No es necesario instalar VSCode.

---

## Paso 1 — Crear cuenta en GitHub

Ir a:

```
https://github.com
```

Crear una cuenta personal.

---

## Paso 2 — Instalar GitHub Desktop

Descargar desde:

```
https://desktop.github.com
```

Instalar el programa e iniciar sesión con la cuenta de GitHub.

GitHub Desktop permite usar Git sin necesidad de usar la terminal.

---

# 4. Crear su propio repositorio para los laboratorios

Cada estudiante debe crear un repositorio donde subirá el código de los laboratorios.

## Paso 1 — Crear el repositorio

En GitHub seleccionar:

```
New repository
```

Configuración recomendada:

Nombre del repositorio:

```
laboratorios-esp32
```

Opciones:

* Public o Private según indique el curso
* Activar la opción **Add README**

Luego seleccionar:

```
Create repository
```

---

# 5. Descargar el repositorio al computador

Abrir **GitHub Desktop**.

Ir a:

```
File → Clone repository
```

Seleccionar el repositorio:

```
laboratorios-esp32
```

Elegir la carpeta donde se guardará en el computador.

Ejemplo:

```
Documentos/
   laboratorios-esp32/
```

Esta carpeta estará sincronizada con GitHub.

---

# 6. Organización recomendada del repositorio

Se recomienda crear una carpeta por cada laboratorio.

Ejemplo:

```
laboratorios-esp32/

   laboratorio1/
      led_blink.ino

   laboratorio2/
      sensor_ultrasonico.ino

   laboratorio3/
      wifi_test.ino
```

Esto permite mantener el repositorio organizado.

---

# 7. Editar el código con Arduino IDE

Abrir la carpeta del laboratorio.

Ejemplo:

```
laboratorio1/
```

Abrir el archivo:

```
led_blink.ino
```

en **Arduino IDE**.

Ejemplo de código:

```cpp
void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}
```

Guardar siempre los archivos **dentro del repositorio**.

---

# 8. Subir el laboratorio a GitHub

Abrir **GitHub Desktop**.

El programa detectará automáticamente los archivos nuevos o modificados.

Ejemplo:

```
laboratorio1/led_blink.ino
```

---

## Paso 1 — Crear un commit

Escribir un mensaje que describa el cambio.

Ejemplo:

```
Laboratorio 1: LED intermitente en ESP32
```

Seleccionar:

```
Commit to main
```

---

## Paso 2 — Subir a GitHub

Presionar:

```
Push origin
```

Esto subirá los cambios al repositorio en GitHub.

---

# 9. Flujo de trabajo para cada laboratorio

Para cada laboratorio se debe seguir el siguiente proceso:

### 1. Crear una carpeta nueva

Ejemplo:

```
laboratorio4/
```

### 2. Guardar el código del ejercicio

Ejemplo:

```
sensor_dht11.ino
```

### 3. Abrir GitHub Desktop

### 4. Crear commit

Ejemplo de mensaje:

```
Laboratorio 4: Lectura de sensor DHT11
```

### 5. Hacer push a GitHub

---

# 10. Qué se evaluará en el repositorio

El repositorio debe mostrar:

* Código funcional
* Organización por carpetas de laboratorio
* Commits con mensajes claros
* Historial de desarrollo

---

# 11. Resumen rápido

| Concepto    | Significado                    |
| ----------- | ------------------------------ |
| Repositorio | Carpeta del proyecto en GitHub |
| Commit      | Registro de cambios            |
| Push        | Subir cambios a GitHub         |
| Pull        | Descargar cambios              |
| Branch      | Rama de desarrollo             |

---

---

# 12. Recursos de instalación

A continuación se incluyen algunos videos que explican el proceso de instalación y uso básico de Git y GitHub. Estos recursos pueden servir como apoyo si se presentan dudas durante la configuración inicial.

## Instalación y configuración básica de Git y GitHub

* Instalación y uso básico de Git y GitHub
  https://www.youtube.com/watch?v=cae7EFzd02M

* Introducción a GitHub y flujo básico de trabajo
  https://www.youtube.com/watch?v=r4ynZyLuf-o

* Uso de GitHub para gestionar proyectos
  https://www.youtube.com/watch?v=mq-CDUwHe8Y

Se recomienda ver al menos uno de estos videos antes de comenzar a utilizar GitHub para los laboratorios.


# Herramientas utilizadas

* Arduino IDE
* GitHub
* GitHub Desktop

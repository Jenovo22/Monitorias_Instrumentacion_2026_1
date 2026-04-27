# PUNTO 3 SPI: Obtención de presión barométrica y temperatura mediante sensor BMP280

## Objetivo
Entender y manejar la interfaz de comunicación serial síncrona **SPI (Serial Peripheral Interface)** para la adquisición de datos climáticos de alta precisión mediante un sensor barométrico.

---

## Descripción general
En este ejercicio se implementa la comunicación entre el ESP32 y el sensor **BMP280** utilizando el bus **VSPI**. El sistema permite obtener lecturas de temperatura, presión atmosférica y una estimación de la altitud, visualizando la información en tiempo real a través del **Monitor Serial**.

---

## Componentes requeridos

| Componente | Cantidad | Descripción |
|-------------|-----------|-------------|
| **ESP32 DevKit** | 1 | Microcontrolador con bus VSPI disponible |
| **Sensor BMP280** | 1 | Sensor de presión y temperatura con interfaz SPI |
| **Cable USB** | 1 | Comunicación y alimentación desde el PC |
| **PC con Arduino IDE** | 1 | Entorno de desarrollo y visualización de datos |

---

## Esquema de conexión

Para este ejercicio se utiliza el bus **VSPI** estándar del ESP32. Es fundamental asegurar que el sensor se alimente con **3.3V**, ya que voltajes superiores pueden dañarlo.

| Pin Sensor (BMP280) | Pin ESP32 (GPIO) | Función SPI |
|---------------------|------------------|-------------|
| **VCC** | 3.3V | Alimentación (Voltaje de referencia) |
| **GND** | GND | Tierra |
| **SCL** | **18** | SCK (Serial Clock) |
| **SDO** | **19** | MISO (Master Input Slave Output) |
| **SDA** | **23** | MOSI (Master Output Slave Input) |
| **CSB** | **5** | CS (Chip Select) |

---

## Lógica del programa

1. **Configuración Inicial:** Se inicializa la comunicación serial a **115200 baudios** y se verifica la conexión física del sensor mediante el bus SPI.
2. **Ajuste de Muestreo:** El sensor se configura en **Modo Normal** con técnicas de *oversampling* y filtrado interno para reducir el ruido en las lecturas de presión.
3. **Adquisición:** En cada ciclo del programa (cada 2 segundos), se extraen los valores de temperatura en °C y presión en hPa.
4. **Cálculo de Altitud:** Se utiliza la presión barométrica actual frente a la presión estándar a nivel del mar (1013.25 hPa) para estimar la altitud en metros.
5. **Visualización:** Se formatea y envía la información al monitor serial para su análisis.

---

## Ajustes y recomendaciones

- **Librerías Obligatorias:** Se debe instalar la librería `Adafruit_BMP280` y su dependencia `Adafruit Unified Sensor` desde el gestor de librerías del IDE.
- **Protocolo Síncrono:** A diferencia de I2C, la interfaz SPI utiliza cuatro hilos de datos y requiere un pin de selección de chip (**CS**) para habilitar la comunicación.
- **Pines VSPI:** Se recomienda usar los pines definidos en la tabla (18, 19, 23 y 5) por ser la configuración de hardware nativa del bus VSPI del ESP32.

---

## Resultados esperados

Al abrir el **Monitor Serial** a **115200 baudios**, se deberá observar el siguiente flujo de datos:

```text
--- INICIANDO SENSOR BMP280 (SPI) ---
Sensor configurado correctamente. Iniciando lecturas...

Temperatura: 24.50 *C
Presion Barometrica: 1012.35 hPa
Altitud Aprox: 120.45 m
------------------------------------

Aquí tienes la estructura completa para el archivo README.md del Punto 3 (Interfaz SPI), diseñada para que la copies y pegues directamente. Se ha omitido el bloque de código y actualizado la autoría según tus instrucciones.

Markdown
# PUNTO 3 SPI: Obtención de presión barométrica y temperatura mediante sensor BMP280

## Objetivo
Entender y manejar la interfaz de comunicación serial síncrona **SPI (Serial Peripheral Interface)** para la adquisición de datos climáticos de alta precisión mediante un sensor barométrico.

---

## Descripción general
En este ejercicio se implementa la comunicación entre el ESP32 y el sensor **BMP280** utilizando el bus **VSPI**. El sistema permite obtener lecturas de temperatura, presión atmosférica y una estimación de la altitud, visualizando la información en tiempo real a través del **Monitor Serial**.

---

## Componentes requeridos

| Componente | Cantidad | Descripción |
|-------------|-----------|-------------|
| **ESP32 DevKit** | 1 | Microcontrolador con bus VSPI disponible |
| **Sensor BMP280** | 1 | Sensor de presión y temperatura con interfaz SPI |
| **Cable USB** | 1 | Comunicación y alimentación desde el PC |
| **PC con Arduino IDE** | 1 | Entorno de desarrollo y visualización de datos |

---

## Esquema de conexión

Para este ejercicio se utiliza el bus **VSPI** estándar del ESP32. Es fundamental asegurar que el sensor se alimente con **3.3V**, ya que voltajes superiores pueden dañarlo.

| Pin Sensor (BMP280) | Pin ESP32 (GPIO) | Función SPI |
|---------------------|------------------|-------------|
| **VCC** | 3.3V | Alimentación (Voltaje de referencia) |
| **GND** | GND | Tierra |
| **SCL** | **18** | SCK (Serial Clock) |
| **SDO** | **19** | MISO (Master Input Slave Output) |
| **SDA** | **23** | MOSI (Master Output Slave Input) |
| **CSB** | **5** | CS (Chip Select) |

---

## Lógica del programa

1. **Configuración Inicial:** Se inicializa la comunicación serial a **115200 baudios** y se verifica la conexión física del sensor mediante el bus SPI.
2. **Ajuste de Muestreo:** El sensor se configura en **Modo Normal** con técnicas de *oversampling* y filtrado interno para reducir el ruido en las lecturas de presión.
3. **Adquisición:** En cada ciclo del programa (cada 2 segundos), se extraen los valores de temperatura en °C y presión en hPa.
4. **Cálculo de Altitud:** Se utiliza la presión barométrica actual frente a la presión estándar a nivel del mar (1013.25 hPa) para estimar la altitud en metros.
5. **Visualización:** Se formatea y envía la información al monitor serial para su análisis.

---

## Ajustes y recomendaciones

- **Librerías Obligatorias:** Se debe instalar la librería `Adafruit_BMP280` y su dependencia `Adafruit Unified Sensor` desde el gestor de librerías del IDE.
- **Protocolo Síncrono:** A diferencia de I2C, la interfaz SPI utiliza cuatro hilos de datos y requiere un pin de selección de chip (**CS**) para habilitar la comunicación.
- **Pines VSPI:** Se recomienda usar los pines definidos en la tabla (18, 19, 23 y 5) por ser la configuración de hardware nativa del bus VSPI del ESP32.

---
/*
 * PRÁCTICA DE INSTRUMENTACIÓN: INTERFAZ SÍNCRONA SPI
 * Ejercicio 3: Sensor BMP280 de Presión y Temperatura
 */
 
 
```cpp 

#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// --- DEFINICIÓN DE PINES SPI (Bus VSPI estándar en ESP32) ---
// Es vital definir estos pines explícitamente para evitar errores de conexión
#define BMP_SCK  18  // Pin de Reloj (Serial Clock)
#define BMP_MISO 19  // Master Input Slave Output (Datos hacia el ESP32)
#define BMP_MOSI 23  // Master Output Slave Input (Datos hacia el sensor)
#define BMP_CS   5   // Chip Select (Selección del dispositivo)

// Crear la instancia del sensor usando la interfaz SPI por hardware
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

void setup() {
  Serial.begin(115200);
  
  // Pausa para asegurar que el monitor serial inicie
  delay(1000);
  Serial.println(F("\n--- INICIANDO SENSOR BMP280 (SPI) ---"));

  // Inicializar el sensor. Si no se encuentra, el programa se detiene.
  if (!bmp.begin()) {
    Serial.println(F("Error: No se encontró un sensor BMP280 válido."));
    Serial.println(F("Verifique las conexiones de los pines SCK, MISO, MOSI y CS."));
    while (1) delay(10); // Bucle infinito de bloqueo
  }

  // Configuración de los parámetros de muestreo del sensor para mayor estabilidad
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operación */
                  Adafruit_BMP280::SAMPLING_X2,     /* Oversampling de Temp */
                  Adafruit_BMP280::SAMPLING_X16,    /* Oversampling de Presión */
                  Adafruit_BMP280::FILTER_X16,      /* Filtrado de ruido */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tiempo de espera (500ms) */
                  
  Serial.println(F("Sensor configurado correctamente. Iniciando lecturas...\n"));
}

void loop() {
  // 1. Lectura de Temperatura (en grados Celsius)
  float temperatura = bmp.readTemperature();

  // 2. Lectura de Presión Barométrica (La librería devuelve Pascales, se divide por 100 para hPa)
  float presion = bmp.readPressure() / 100.0F;

  // 3. Lectura de Altitud aproximada (Requiere la presión a nivel del mar local, por defecto 1013.25)
  float altitud = bmp.readAltitude(1013.25);

  // --- PRESENTACIÓN DE DATOS (Monitor Serial) ---
  Serial.print(F("Temperatura: "));
  Serial.print(temperatura);
  Serial.println(F(" *C"));

  Serial.print(F("Presion Barometrica: "));
  Serial.print(presion);
  Serial.println(F(" hPa"));

  Serial.print(F("Altitud Aprox: "));
  Serial.print(altitud);
  Serial.println(F(" m"));

  Serial.println(F("------------------------------------"));

  // Pausa de 2 segundos entre lecturas
  delay(2000); 
}

```

## Resultados esperados

Al abrir el **Monitor Serial** a **115200 baudios**, se deberá observar el siguiente flujo de datos:

```text
--- INICIANDO SENSOR BMP280 (SPI) ---
Sensor configurado correctamente. Iniciando lecturas...

Temperatura: 24.50 *C
Presion Barometrica: 1012.35 hPa
Altitud Aprox: 120.45 m
------------------------------------
👨‍💻 Autor
Jerónimo Novoa Giraldo Proyecto de práctica con comunicación SPI e instrumentación climática usando ESP32 + BMP280, desarrollado para el curso de Instrumentación Electrónica.
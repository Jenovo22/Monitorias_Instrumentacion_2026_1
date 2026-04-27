# PUNTO 4: Conectividad Inalámbrica y Protocolos IoT (Bluetooth, WiFi y MQTT)

## 👨‍💻 Autor
**Jerónimo Novoa Giraldo** Práctica de **Conectividad y Sistemas Embebidos** para el curso de **Instrumentación Electrónica** en la **Universidad Nacional**.

---

## 1. Comparativa de Protocolos de Comunicación
Para que el estudiante diferencie las tecnologías utilizadas en esta práctica:

| Característica | 4a. Bluetooth Classic (SPP) | 4b. WiFi (Modo Estación) | 4c. MQTT (Sobre TCP/IP y WebSockets) |
| :--- | :--- | :--- | :--- |
| **Alcance** | Corto (10-15 metros). | Medio (Depende del Router). | Global (Vía Internet). |
| **Arquitectura** | Maestro-Esclavo (Punto a Punto). | Cliente-Servidor. | Publicador-Suscriptor (Broker). |
| **Uso Ideal** | Reemplazo inalámbrico del cable serial. | Acceso a redes locales/web. | Interfaz Web (HMI) y telemetría IoT. |
| **Limitación** | Solo conexión local cercana. | Consume mucha potencia. | Requiere un Broker intermedio. |

---

## 2. Identificación Única de Dispositivo
En el laboratorio de la **UNAL**, habrá muchos ESP32 encendidos. Para no confundir los datos:

1. **SSID/Name:** El nombre del dispositivo en el código debe incluir tu nombre (ej. `ESP32_UNAL_TuNombre`).
2. **Dirección MAC:** Es la "cédula" del chip. El código imprimirá este identificador en el Monitor Serial. Úsalo para verificar que el dispositivo que ves es realmente el tuyo.
3. **ClientID MQTT:** Si dos personas usan el mismo ID de cliente, el servidor los desconectará constantemente. Usa un ID único (ej. `UN_Client_TuApellido`).

---

## 3. Desarrollo de la Práctica

### 4a. Comunicación Bluetooth (Classic)
El ESP32 funciona como un puente serie inalámbrico para enviar y recibir datos.

* **Aplicación Recomendada (Android):** [**Serial Bluetooth Terminal**](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal).
    * **Por qué Android:** Apple bloquea el protocolo Bluetooth Classic (SPP) en iPhones para apps de terceros. En Android, esta app permite crear botones (macros) y ver la comunicación en tiempo real de forma abierta.
* **Prueba:** Enviar un comando desde el celular y verificar que el ESP32 responda o ejecute una acción.

/*
 * PRÁCTICA DE INSTRUMENTACIÓN: COMUNICACIÓN INDUSTRIAL
 * Ejercicio 4 - Fase A: Enlace Bluetooth Serial con Potenciómetro (Doble Salida)
 */

 ```cpp 

#include "BluetoothSerial.h"

// Verificar si el Bluetooth está habilitado en la configuración del ESP32
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error "El Bluetooth no está habilitado. Verifica tu configuración o placa."
#endif

// Crear una instancia del objeto Bluetooth
BluetoothSerial SerialBT;

// --- DEFINICIÓN DE PINES ---
const int pinLED = 2;            // Usamos el LED azul integrado en la placa
const int pinPotenciometro = 34; // Pin análogo para el potenciómetro

// Variables para control de tiempo (telemetría no bloqueante)
unsigned long tiempoAnterior = 0;
const long intervalo = 3000; // Enviar valor del potenciómetro cada 3 segundos

void setup() {
  // Inicializar el puerto serial convencional (USB hacia el PC)
  Serial.begin(115200);
  
  // Configuración de pines
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);

  // Inicializar el Bluetooth con el nombre que aparecerá en el celular
  SerialBT.begin("ESP32_Grupo1"); // Sugiere a los alumnos cambiar este nombre
  
  // Mensajes iniciales en el Monitor Serial del PC
  Serial.println("--- SISTEMA INICIADO ---");
  Serial.println("El dispositivo Bluetooth esta listo.");
  Serial.println("Esperando emparejamiento con el celular...");
}

void loop() {
  // 1. RECEPCIÓN DE COMANDOS DESDE EL CELULAR
  if (SerialBT.available()) {
    char comando = SerialBT.read();
    
    // Ignorar saltos de línea del terminal
    if (comando != '\n' && comando != '\r') {
      Serial.print("Comando recibido vía BT: ");
      Serial.println(comando);
    }

    // Lógica de control del LED e interrogación manual
    if (comando == '1') {
      digitalWrite(pinLED, HIGH);
      SerialBT.println("Confirmacion: LED ENCENDIDO");
      Serial.println("-> Accion Local: El celular encendio el LED."); // Reflejo en PC
    } 
    else if (comando == '0') {
      digitalWrite(pinLED, LOW);
      SerialBT.println("Confirmacion: LED APAGADO");
      Serial.println("-> Accion Local: El celular apago el LED."); // Reflejo en PC
    }
    else if (comando == 'P' || comando == 'p') {
      // Si el usuario pide el valor del potenciómetro manualmente
      int valorPot = analogRead(pinPotenciometro);
      SerialBT.print("Lectura solicitada (ADC): ");
      SerialBT.println(valorPot);
      
      Serial.print("-> El celular solicito lectura. Valor enviado: ");
      Serial.println(valorPot); // Reflejo en PC
    }
  }

  // 2. ENVÍO PERIÓDICO DE DATOS (Telemetría)
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
    
    // Leer el convertidor análogo a digital (0 a 4095)
    int valorPot = analogRead(pinPotenciometro);
    
    // Enviar el dato por Bluetooth al celular
    SerialBT.print("Telemetria BT - Potenciometro: ");
    SerialBT.println(valorPot);
    
    // Enviar el mismo dato por el Monitor Serial al computador
    Serial.print("Telemetria PC - Potenciometro: ");
    Serial.println(valorPot);
  }
}
```

---

### 4b. Conectividad WiFi (Modo Estación)
El ESP32 se conecta a una red para obtener salida a internet o red local.

* **Frecuencia Obligatoria:** El chip solo trabaja en **2.4 GHz**. No intentes conectar a redes 5 GHz.
* **Red de la Universidad:** **No utilizar la red WiFi de la UNAL**. Sus firewalls y protocolos WPA2-Enterprise impiden la conexión de microcontroladores y bloquean la visibilidad entre dispositivos.
* **Recomendación:** Usar un móvil **Android** como Hotspot (Punto de acceso). Es más estable y fácil de configurar en 2.4 GHz que un iPhone.

/*
 * PRÁCTICA DE INSTRUMENTACIÓN: COMUNICACIÓN INDUSTRIAL
 * Ejercicio 4 - Fase B: Servidor Web WiFi Local
 */

```cpp 
#include <WiFi.h>

// --- CREDENCIALES DE RED WIFI ---
// TODO: Los estudiantes deben poner el nombre y contraseña de su red (o compartir datos desde el celular)
const char* ssid     = "Gilcito";
const char* password = "Pandequeso";

// Configurar el servidor web en el puerto 80 (estándar HTTP)
WiFiServer server(80);

// --- DEFINICIÓN DE PINES ---
const int pinLED = 2;             // LED integrado en la placa ESP32
const int pinPotenciometro = 34;  // Pin análogo de solo entrada

// Variable para almacenar el estado del LED
String estadoLED = "APAGADO";

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW); // Asegurar que inicie apagado

  // 1. Conexión a la red WiFi
  Serial.print("Conectando a la red: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  // Bucle de espera hasta que se establezca la conexión
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n¡Conexión WiFi exitosa!");
  
  // 2. Iniciar el servidor web
  server.begin();
  
  // Mostrar la dirección IP asignada al ESP32 (clave para acceder desde el celular)
  Serial.print("Servidor Web iniciado. Para acceder, abre un navegador y escribe esta IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Verificar si algún cliente (navegador web) se ha conectado
  WiFiClient client = server.available();

  if (client) {
    Serial.println("¡Nuevo cliente conectado!");
    String peticionHTTP = "";
    
    // Leer los datos enviados por el cliente
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        peticionHTTP += c;
        
        // Si la petición HTTP termina (con un salto de línea doble)
        if (c == '\n' && peticionHTTP.endsWith("\r\n\r\n")) {
          
          // --- LÓGICA DE CONTROL (Análisis de la URL) ---
          // Si la petición contiene "GET /LED=ON"
          if (peticionHTTP.indexOf("GET /LED=ON") >= 0) {
            Serial.println("Comando Web: Encender LED");
            estadoLED = "ENCENDIDO";
            digitalWrite(pinLED, HIGH);
          } 
          // Si la petición contiene "GET /LED=OFF"
          else if (peticionHTTP.indexOf("GET /LED=OFF") >= 0) {
            Serial.println("Comando Web: Apagar LED");
            estadoLED = "APAGADO";
            digitalWrite(pinLED, LOW);
          }

          // --- LECTURA DEL SENSOR ---
          int valorPot = analogRead(pinPotenciometro);

          // --- CONSTRUCCIÓN DE LA PÁGINA WEB (HTML) ---
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
          
          // Código HTML enviado al navegador
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<title>Servidor ESP32</title>");
          // Refrescar la página automáticamente cada 3 segundos para actualizar el potenciómetro
          client.println("<meta http-equiv=\"refresh\" content=\"3\">"); 
          client.println("<style>body { font-family: Arial; text-align: center; margin: 50px;} ");
          client.println(".boton { background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-decoration: none; font-size: 20px; margin: 10px; cursor: pointer; border-radius: 10px;} ");
          client.println(".boton-off { background-color: #f44336; }</style></head>");
          client.println("<body><h1>Panel de Control ESP32</h1>");
          
          // Mostrar datos del Potenciómetro
          client.println("<h2>Lectura del Potenciometro: <span style=\"color:blue;\">" + String(valorPot) + "</span></h2>");
          
          // Mostrar estado del LED y Botones
          client.println("<h3>Estado del LED: " + estadoLED + "</h3>");
          client.println("<a href=\"/LED=ON\"><button class=\"boton\">ENCENDER LED</button></a>");
          client.println("<a href=\"/LED=OFF\"><button class=\"boton boton-off\">APAGAR LED</button></a>");
          
          client.println("</body></html>");
          
          // La respuesta HTTP termina con una línea en blanco
          client.println();
          break; // Salir del bucle while
        }
      }
    }
    // Cerrar la conexión para liberar al cliente
    client.stop();
    Serial.println("Cliente desconectado.\n");
  }
}

```
---

### 4c. Protocolo de Mensajería MQTT y Visualización Web (HMI)
Uso de un Broker público para enviar datos de sensores y visualizarlos en una página web, logrando una comunicación bidireccional (ESP32 <-> Broker <-> HTML).

**Entendiendo los Tópicos (Jerarquía de carpetas):**
Los tópicos funcionan como rutas de archivos. Para evitar interferencias con otros grupos, usa esta estructura:
* `UNAL/Instrumentacion/TuNombre/Potenciometro`
* `UNAL/Instrumentacion/TuNombre/ControlLED`

**Visualización y Control mediante Página Web (HTML/JS):**
* **Sin aplicaciones extra:** No es necesario instalar ninguna app de celular ni un servidor local. Se utiliza un archivo `.html` (que contiene HTML y JavaScript) y se abre directamente en el navegador del computador.
* **MQTT sobre WebSockets:** Para que la página web se comunique con el Broker, se utiliza el protocolo WebSockets (usualmente por el puerto **8000**), mientras que el ESP32 sigue usando el puerto MQTT estándar (1883).
* **Interacción:** A través de la interfaz web, el estudiante podrá ver la gráfica o el valor del potenciómetro actualizándose en tiempo real y tendrá botones para controlar el encendido/apagado del actuador (LED) conectado al ESP32.

/*
 * PRÁCTICA DE INSTRUMENTACIÓN: COMUNICACIÓN INDUSTRIAL
 * Ejercicio 4 - Fase C: MQTT Bidireccional (Potenciómetro y LED)
 */

```cp
#include <WiFi.h>
#include <PubSubClient.h>

// --- CREDENCIALES DE RED WIFI ---
const char* ssid = "Gilcito";
const char* password = "Pandequeso";

// --- CONFIGURACIÓN MQTT ---
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// Tópicos MQTT (Deben ser idénticos en el HTML)
const char* topic_potenciometro = "instrumentacion/grupo1/potenciometro";
const char* topic_control = "instrumentacion/grupo1/control";

// --- DEFINICIÓN DE PINES ---
const int pinLED = 2;             // LED azul integrado en la placa
const int pinPotenciometro = 34;  // Pin análogo de solo entrada

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long tiempoAnterior = 0;
const long intervalo = 2000; // Enviar datos del potenciómetro cada 2 segundos

void setup_wifi() {
  delay(10);
  Serial.println("\n--- SISTEMA MQTT INICIADO ---");
  Serial.print("Conectando a la red WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado exitosamente.");
  Serial.print("IP asignada: ");
  Serial.println(WiFi.localIP());
}

// Función que se ejecuta al recibir un mensaje del broker (Control del LED)
void callback(char* topic, byte* payload, unsigned int length) {
  String mensaje = "";
  for (int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }
  
  Serial.print("Comando recibido en [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(mensaje);

  // Lógica de control del LED
  if (mensaje == "1") {
    digitalWrite(pinLED, HIGH);
    Serial.println("-> Accion: LED ENCENDIDO");
  } 
  else if (mensaje == "0") {
    digitalWrite(pinLED, LOW);
    Serial.println("-> Accion: LED APAGADO");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexion al Broker MQTT...");
    // ID de cliente único
    String clientId = "ESP32_Lab_" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("¡Conectado!");
      // Suscribirse al tópico de control para escuchar comandos de la web
      client.subscribe(topic_control);
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(" - Reintentando en 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  
  setup_wifi();
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); // Asignar la función de recepción
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Mantener viva la conexión y escuchar mensajes entrantes

  // Publicación periódica del Potenciómetro
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
    
    // Leer el valor del ADC (0 a 4095)
    int valorPot = analogRead(pinPotenciometro);
    
    // Convertir el número a texto (String) para enviarlo por MQTT
    String payload = String(valorPot);
    
    Serial.print("Publicando Potenciometro: ");
    Serial.println(payload);
    
    // Enviar el dato al broker
    client.publish(topic_potenciometro, payload.c_str());
  }
}
```

```cp
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>HMI MQTT - Laboratorio de Instrumentación</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/paho-mqtt/1.0.1/mqttws31.min.js" type="text/javascript"></script>
    <style>
        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; text-align: center; background-color: #e9ecef; margin-top: 40px; }
        .panel { background: white; width: 90%; max-width: 450px; margin: auto; padding: 30px; border-radius: 12px; box-shadow: 0px 4px 15px rgba(0,0,0,0.2); }
        h1 { color: #343a40; font-size: 24px; }
        .estado { font-size: 14px; padding: 10px; border-radius: 5px; margin-bottom: 25px; font-weight: bold; }
        .desconectado { background-color: #f8d7da; color: #721c24; }
        .conectado { background-color: #d4edda; color: #155724; }
        .lectura-caja { background-color: #f8f9fa; border: 2px solid #dee2e6; border-radius: 10px; padding: 20px; margin-bottom: 30px; }
        .dato { font-size: 50px; color: #007bff; font-weight: bold; margin: 10px 0; }
        button { padding: 15px 0; font-size: 18px; font-weight: bold; color: white; border: none; border-radius: 8px; cursor: pointer; margin: 10px 2%; width: 45%; transition: 0.3s; }
        .btn-on { background-color: #28a745; }
        .btn-on:hover { background-color: #218838; }
        .btn-off { background-color: #dc3545; }
        .btn-off:hover { background-color: #c82333; }
    </style>
</head>
<body>

    <div class="panel">
        <h1>Panel de Control IoT</h1>
        <div id="estado-conexion" class="estado desconectado">Conectando al Broker...</div>
        
        <div class="lectura-caja">
            <h2 style="margin: 0; color: #6c757d; font-size: 18px;">Valor del Potenciómetro (ADC)</h2>
            <div class="dato" id="valor-pot">---</div>
        </div>
        
        <hr style="border: 1px solid #eee; margin-bottom: 25px;">
        
        <h2 style="margin: 0 0 15px 0; color: #6c757d; font-size: 18px;">Control del LED (Actuador)</h2>
        <div>
            <button class="btn-on" onclick="enviarComando('1')">ENCENDER</button>
            <button class="btn-off" onclick="enviarComando('0')">APAGAR</button>
        </div>
    </div>

    <script>
        // --- CONFIGURACIÓN DEL BROKER ---
        const broker = "broker.hivemq.com";
        const puerto = 8000; // Puerto WebSocket (Obligatorio para HTML)
        const clientId = "Web_" + Math.random().toString(16).substr(2, 8);
        
        // Tópicos MQTT
        const topicPotenciometro = "instrumentacion/grupo1/potenciometro";
        const topicControl = "instrumentacion/grupo1/control";

        // Instancia del cliente MQTT
        const client = new Paho.MQTT.Client(broker, puerto, clientId);

        // Callbacks
        client.onConnectionLost = onConnectionLost;
        client.onMessageArrived = onMessageArrived;

        // Opciones de conexión
        const options = {
            timeout: 3,
            onSuccess: onConnect,
            onFailure: function (message) {
                const estadoDiv = document.getElementById("estado-conexion");
                estadoDiv.className = "estado desconectado";
                estadoDiv.innerHTML = "Error de conexión: " + message.errorMessage;
            }
        };

        // Iniciar conexión automáticamente al abrir la página
        client.connect(options);

        // Al conectarse exitosamente
        function onConnect() {
            console.log("Conectado al broker MQTT");
            const estadoDiv = document.getElementById("estado-conexion");
            estadoDiv.className = "estado conectado";
            estadoDiv.innerHTML = "🟢 Conectado al Servidor";
            
            // Suscribirse para escuchar el potenciómetro
            client.subscribe(topicPotenciometro);
        }

        // Si se pierde la conexión
        function onConnectionLost(responseObject) {
            if (responseObject.errorCode !== 0) {
                const estadoDiv = document.getElementById("estado-conexion");
                estadoDiv.className = "estado desconectado";
                estadoDiv.innerHTML = "🔴 Desconectado: " + responseObject.errorMessage;
            }
        }

        // Al recibir un mensaje del ESP32
        function onMessageArrived(message) {
            if (message.destinationName === topicPotenciometro) {
                // Actualizar el número gigante en la pantalla
                document.getElementById("valor-pot").innerHTML = message.payloadString;
            }
        }

        // Al presionar los botones de control
        function enviarComando(estado) {
            if (client.isConnected()) {
                const message = new Paho.MQTT.Message(estado);
                message.destinationName = topicControl;
                client.send(message);
                console.log("Comando publicado: " + estado);
            } else {
                alert("Espera a que el sistema se conecte al servidor.");
            }
        }
    </script>
</body>
</html>

```

---

## ⚠️ Recomendaciones Finales
1.  **Antena:** No cubras la parte metálica en zigzag del ESP32; es la antena y cualquier obstrucción causará desconexiones.
2.  **Alimentación:** El WiFi genera picos de consumo. Si el dispositivo se reinicia (Brownout), verifica que el cable USB sea de buena calidad y esté conectado directamente a un puerto con buena potencia.
3.  **Firewalls y Errores de Conexión:** Si al abrir la página web sale un error de *"Connect timed out"* o el ESP32 muestra *"rc=-2"*, significa que la red en la que están conectados bloquea los puertos 1883 y 8000. Utilice siempre los datos compartidos de un celular para garantizar la conexión.
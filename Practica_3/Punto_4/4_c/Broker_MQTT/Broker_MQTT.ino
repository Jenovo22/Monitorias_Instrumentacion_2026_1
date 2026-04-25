/*
 * PRÁCTICA DE INSTRUMENTACIÓN: COMUNICACIÓN INDUSTRIAL
 * Ejercicio 4 - Fase C: MQTT Bidireccional (Potenciómetro y LED)
 */

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
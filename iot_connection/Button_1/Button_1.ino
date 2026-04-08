#include <WiFi.h>
#include <PubSubClient.h>

// 🔹 WiFi
const char* ssid = "Novoa";
const char* password = "1234567890";

// 🔹 MQTT Broker
const char* mqtt_server = "broker.emqx.io";

WiFiClient espClient;
PubSubClient client(espClient);

// 🔹 Pines
const int botonPin = 4;
const int ledPin = 23;

int estadoBoton = 0;
int estadoAnterior = 1;
int contador = 0;

// ------------------ WIFI ------------------
void setup_wifi() {
  Serial.print("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Conectado a WiFi");
}

// ------------------ MQTT CALLBACK ------------------
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;

  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  Serial.println("📩 Mensaje recibido: " + msg);

  // 🔥 Botón virtual desde la web
  if (msg.indexOf("web") >= 0) {
    contador++;

    Serial.println("🌐 Botón WEB presionado");

    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);

    // enviar actualización
    String payloadOut = "{";
    payloadOut += "\"contador\": " + String(contador);
    payloadOut += "}";

    client.publish("esp32/boton", payloadOut.c_str());
  }
}

// ------------------ MQTT RECONNECT ------------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando a MQTT...");

    if (client.connect("ESP32_Button")) {
      Serial.println("✅ conectado");
      client.subscribe("esp32/boton");
    } else {
      Serial.print("❌ error, rc=");
      Serial.print(client.state());
      Serial.println(" reintentando...");
      delay(2000);
    }
  }
}

// ------------------ SETUP ------------------
void setup() {
  Serial.begin(115200);

  pinMode(botonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

// ------------------ LOOP ------------------
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  estadoBoton = digitalRead(botonPin);

  // 🔹 Botón físico
  if (estadoBoton == LOW && estadoAnterior == HIGH) {
    contador++;

    Serial.println("🔘 Botón físico presionado");

    digitalWrite(ledPin, HIGH);

    String payload = "{";
    payload += "\"contador\": " + String(contador);
    payload += "}";

    client.publish("esp32/boton", payload.c_str());
  }

  if (estadoBoton == HIGH) {
    digitalWrite(ledPin, LOW);
  }

  estadoAnterior = estadoBoton;

  delay(50);
}
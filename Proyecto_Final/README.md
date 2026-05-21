# Proyecto Final - Instrumentación Electrónica

## Introducción

El proyecto final de la asignatura de Instrumentación Electrónica tiene como objetivo que cada grupo implemente un sistema básico de medición, actuación y comunicación usando su sistema embebido principal.

Cada proyecto debe integrar al menos un sensor, un actuador y una lógica de funcionamiento. Se espera que exista una relación clara entre la variable medida y la acción que realiza el actuador.

Además, todos los proyectos deberán incluir una conexión MQTT para enviar información desde la ESP32 o el embedido de su elección hacia un broker en la nube. Para esta implementación se recomienda usar el broker público de EMQX, ya que es de fácil acceso, permite pruebas rápidas y ya fue utilizado en la práctica anterior.

---

## Consideraciones a tener en cuenta

Antes de iniciar el montaje, cada grupo debe responder las siguientes preguntas mínimas:

- ¿Qué sensor van a usar?
- ¿Qué actuador van a mover o encender?
- ¿Qué condición activará el actuador?
- ¿Qué dato enviará el ESP32 al broker MQTT?
- ¿Qué mostrará el dashboard, monitor serial o pantalla local?

Ejemplo:

Si la temperatura medida es mayor a 30 °C, entonces el ESP32 enciende un ventilador. Además, publica por MQTT la temperatura medida y el estado del ventilador.

---

## Requisito mínimo de IoT

Todos los grupos deben publicar al menos una variable medida desde el embedido hacia un broker MQTT alojado en la nube. Opcionalmente, también podrán recibir comandos desde el dashboard para activar o desactivar actuadores.

Para el desarrollo del proyecto se recomienda utilizar el broker público de EMQX:

- Broker: broker.emqx.io
- Puerto MQTT TCP: 1883
- Puerto MQTT WebSocket: 8083
- Puerto MQTT seguro TLS: 8883
- Puerto WebSocket seguro WSS: 8084

Este broker es de uso público y resulta útil para pruebas, prototipos y aplicaciones académicas en la nube. Como es un broker público, no deben enviarse contraseñas, datos personales, información privada ni datos sensibles.

Ejemplo de estructura de topics MQTT:

instrumentacion/2026_1/grupo01/proyecto01/data  
instrumentacion/2026_1/grupo01/proyecto01/status  
instrumentacion/2026_1/grupo01/proyecto01/cmd  

Ejemplo de mensaje en formato JSON:

{
  "grupo": 1,
  "proyecto": "monitoreo_ambiental",
  "temperatura": 28.5,
  "humedad": 62,
  "actuador": "OFF"
}

---

# Guía por proyecto

## 1. Tacómetro óptico con control de motor

Este proyecto consiste en medir la velocidad de giro de un motor usando un sensor óptico reflectivo o un fotointerruptor. La implementación mínima sugerida es que el ESP32 detecte los pulsos generados por el sensor, calcule una velocidad aproximada en RPM y muestre el valor en el monitor serial, una pantalla OLED o un display. El actuador recomendado es un motor DC pequeño, que puede encenderse directamente mediante un módulo driver o controlarse con PWM. Como mejora opcional, el grupo puede variar la velocidad del motor desde el ESP32, publicar las RPM por MQTT y permitir que desde el dashboard se cambie una velocidad deseada. Implementos recomendados: ESP32, sensor TCRT5000 o fotointerruptor, motor DC pequeño, MOSFET o driver de motor, fuente externa para el motor, resistencias, cables, protoboard, OLED o display opcional. Tutorial similar: [RPM Calculator with Speed control ESP32 & OLED with BO motor Encoder Wheel](https://www.youtube.com/watch?v=bTc2g1U-YpE)

---

## 2. Estación de monitoreo ambiental con control de extractor

Este proyecto mide variables ambientales como temperatura, humedad y presencia aproximada de gases. La implementación mínima sugerida es conectar un sensor DHT22 al ESP32 para medir temperatura y humedad, y un sensor MQ-135 o MQ-2 para obtener una lectura aproximada de calidad de aire o gases. El actuador puede ser un ventilador DC o extractor pequeño que se encienda cuando la temperatura o el nivel del sensor de gas supere un umbral definido por el grupo. Como mejora opcional, el grupo puede publicar por MQTT la temperatura, humedad, lectura del gas y estado del ventilador, además de permitir el encendido manual desde un dashboard. Implementos recomendados: ESP32, DHT22 para humedad, MQ-135 o MQ-2 para calidad del aire, ventilador DC de 5 V o 12 V, MOSFET o relé, diodo de protección si aplica, fuente externa, LEDs, buzzer y pantalla OLED/LCD opcional. Tutorial similar: [How to use MQ135 Gas Sensor with ESP32 using BLYNK IoT Cloud & LCD Display](https://www.youtube.com/watch?v=oMS7RVJY_Bk)

---

## 3. Medidor de radiación solar con control de orientación

Este proyecto busca orientar un panel o maqueta hacia la zona de mayor iluminación. La implementación mínima sugerida es usar dos o cuatro LDR organizadas en forma de cruz para comparar la cantidad de luz recibida en cada dirección. El ESP32 lee las LDR y mueve un servomotor hacia el lado donde detecte mayor intensidad luminosa. No se requiere un control avanzado; basta con una lógica simple de comparación entre sensores. Como mejora opcional, el grupo puede publicar por MQTT la intensidad de luz y la posición aproximada del servo, o agregar un segundo eje de movimiento. Implementos recomendados: ESP32, 2 o 4 LDR, resistencias de 10 kΩ, servomotor SG90 o similar, estructura mecánica sencilla, protoboard, cables y fuente externa si el servo consume demasiada corriente. Tutorial similar: [SolarLink | ESP32 Sun Tracking Solar Panels Tutorial](https://www.youtube.com/watch?v=hpn9lz57NCg)

---

## 4. Medidor de radiación ultravioleta o luminosidad con control de persiana

Este proyecto consiste en medir la exposición a luz o radiación UV y mover una persiana simulada. La implementación mínima sugerida es usar un sensor UV como ML8511 o VEML6075; si el grupo no cuenta con estos sensores, puede usar una LDR y aclarar que en ese caso el sistema mide luminosidad, no radiación UV real. El actuador será un servomotor que abra o cierre una persiana pequeña según el nivel medido. Como mejora opcional, pueden publicar por MQTT el nivel de luz o UV y la posición de la persiana, además de permitir abrir o cerrar desde un dashboard. Implementos recomendados: ESP32, ML8511, VEML6075 o LDR, servomotor SG90, resistencias, estructura de persiana simulada, LEDs, buzzer y pantalla pequeña opcional. Tutorial similar: [Smart Curtain control using Servo & LDR](https://circuitdigest.com/microcontroller-projects/diy-smart-curtains-using-esp32-and-ldr-sensors)

---

## 5. Sistema de medición y control de nivel en tanque con sensor ultrasónico

Este proyecto mide el nivel de un tanque usando un sensor ultrasónico. La implementación mínima sugerida es ubicar el HC-SR04 en la parte superior del tanque para medir la distancia hasta la superficie del agua. El ESP32 puede convertir esa distancia en un nivel aproximado y activar una bomba, válvula o LED indicador cuando el nivel sea menor o mayor a cierto umbral. Como mejora opcional, el grupo puede publicar por MQTT el nivel del tanque y el estado de la bomba, además de permitir activar o desactivar la bomba desde el dashboard. Implementos recomendados: ESP32, HC-SR04, bomba de agua 5 V o 12 V, MOSFET o relé, diodo de protección, fuente externa, manguera, recipiente, cables y pantalla opcional. Tutorial similar: [ESP32 water level monitoring system](https://www.youtube.com/watch?v=WeYxrAFxd7M)

---

## 6. Sistema de control de calidad de bebidas

Este proyecto simula la evaluación de calidad de un líquido usando variables como turbidez, conductividad o temperatura. La implementación mínima sugerida es construir una pequeña cámara de medición con un LED y una LDR para estimar turbidez: si pasa mucha luz, el líquido es más claro; si pasa poca luz, el líquido es más turbio. También pueden usar una medición sencilla de conductividad para diferenciar líquidos, aclarando que esto no reemplaza un sensor de pH real. El actuador puede ser un servo que simule aceptar o rechazar la bebida, acompañado de LEDs o buzzer. Como mejora opcional, el grupo puede publicar por MQTT la lectura de turbidez, temperatura o estado de aceptación/rechazo. Implementos recomendados: ESP32, LDR, LED, resistencias, recipiente transparente, sensor de temperatura opcional, cables, servo SG90, LEDs, buzzer y pantalla opcional. Tutorial similar: [Water Quality Monitoring System: TDS Sensor + ESP32/Arduino](https://www.hackatronic.com/water-quality-monitoring-system-tds-sensor-esp32-arduino/)

---

## 7. Sistema didáctico de control térmico de baja potencia

Este proyecto mide y regula de forma sencilla la temperatura de una maqueta. La implementación mínima sugerida es usar un sensor de temperatura como DS18B20, DHT22 o LM35 para medir la temperatura del sistema. El actuador puede ser un bombillo pequeño, resistencia calefactora de baja tensión o ventilador. La lógica puede ser simple: si la temperatura está por debajo de un valor, se activa la fuente de calor; si supera el valor, se apaga o se enciende un ventilador. Como mejora opcional, el grupo puede publicar por MQTT la temperatura y el estado del actuador, además de graficar la evolución de la temperatura en el dashboard. Implementos recomendados: ESP32, sensor de temperatura, resistencia calefactora de 12 V o bombillo de baja potencia, MOSFET o relé, fuente externa, ventilador opcional, LEDs, buzzer opcional y pantalla. Tutorial similar: [ESP32 & DS18B20 Temperature Sensor](https://www.youtube.com/watch?v=SdR2TXewC_o)

---

## 8. Sistema de medición y registro de consumo eléctrico en DC

Este proyecto mide el consumo eléctrico de una carga de baja tensión. La implementación mínima sugerida es usar el sensor INA219, ya que permite medir voltaje, corriente y potencia mediante comunicación I2C con el ESP32. La carga puede ser un motor DC pequeño, una resistencia de potencia, un bombillo de 12 V o una tira LED. El sistema debe mostrar voltaje, corriente y potencia en el monitor serial, pantalla local o dashboard. Como mejora opcional, el grupo puede estimar energía consumida con el tiempo y publicar por MQTT voltaje, corriente, potencia y energía acumulada. Implementos recomendados: ESP32, INA219, carga DC de 5 V a 12 V, fuente externa, cables, protoboard, pantalla OLED/LCD opcional y multímetro para comparación básica. Tutorial similar: [Interfacing INA219 Current Sensor Module with ESP32](https://iamleon99.blogspot.com/2023/05/arduino-interfacing-ina219-current.html)

---

## 9. Clasificador de piezas por tamaño

Este proyecto clasifica piezas según su tamaño o altura. La implementación mínima sugerida es usar un sensor ultrasónico HC-SR04 o un sensor ToF VL53L0X para medir la distancia hasta la pieza. Según el valor medido, el ESP32 mueve un servomotor hacia una posición diferente para simular la clasificación de piezas pequeñas, medianas o grandes. La banda transportadora puede ser real o simulada; si no se cuenta con banda, las piezas pueden ubicarse manualmente frente al sensor. Como mejora opcional, el grupo puede contar cuántas piezas de cada tipo han sido clasificadas y publicar el conteo por MQTT. Implementos recomendados: ESP32, HC-SR04 o VL53L0X, servo SG90, piezas de diferentes alturas, estructura de clasificación, motor DC para banda opcional, driver o MOSFET, LEDs y pantalla opcional. Tutorial similar: [Como hacer una cinta transportadora, selección por tamaño](https://www.youtube.com/watch?v=z423DCyCrdk)

---

## 10. Sistema de clasificación de material reciclable simulado

Este proyecto clasifica objetos según su color o tono. La implementación mínima sugerida es usar un sensor de color TCS3200 o TCS34725 para identificar si un objeto es claro, oscuro o de un color específico. El ESP32 procesa la lectura y activa un servomotor para dirigir el objeto hacia un compartimento. Si no se cuenta con una banda transportadora, el objeto puede colocarse manualmente frente al sensor. Como mejora opcional, el grupo puede publicar por MQTT el color detectado, la categoría asignada y el número de objetos clasificados. Implementos recomendados: ESP32, sensor TCS3200 o TCS34725, servo SG90, objetos de prueba, estructura de clasificación, sensor IR de presencia opcional, LEDs, buzzer y pantalla opcional. Tutorial similar: [TCS3200 Color Recognition Sensor ESP32 LCD || Arduino Color Sensing - TCS230 TCS3200 Color Sensor](https://www.youtube.com/watch?v=x8KI2BRp7ek)

---

## 11. Invernadero didáctico automatizado

Este proyecto controla variables básicas de una maqueta de invernadero. La implementación mínima sugerida es medir temperatura y humedad ambiental con un DHT22, humedad del suelo con un sensor capacitivo y luz con una LDR o BH1750. Según los valores medidos, el ESP32 puede activar una bomba de riego, un ventilador o una luz LED. La lógica puede basarse en umbrales sencillos: si el suelo está seco, activar bomba; si la temperatura es alta, activar ventilador; si hay poca luz, encender LED. Como mejora opcional, el grupo puede publicar por MQTT temperatura, humedad, humedad del suelo, luz y estado de actuadores, además de permitir activar bomba, ventilador o luz desde el dashboard. Implementos recomendados: ESP32, DHT22, sensor capacitivo de humedad de suelo, LDR o BH1750, bomba de agua 5 V, ventilador 12 V, tira LED o LED de potencia, MOSFETs o relés, fuente externa, manguera, recipiente y maqueta de invernadero. Tutorial similar: [ESP32 Automatic Plant Watering IoT Project](https://www.youtube.com/watch?v=K11lxI0kJVM)

---

## 12. Mini simulador de control de acceso industrial

Este proyecto simula un sistema de acceso usando tarjetas RFID. La implementación mínima sugerida es conectar un lector RC522 al ESP32 para leer una tarjeta o llavero RFID. Si la tarjeta está autorizada, el ESP32 activa un servo, solenoide o cerradura simulada; si no está autorizada, activa un LED rojo o buzzer. Como mejora opcional, el grupo puede publicar por MQTT cada intento de acceso, indicando si fue permitido o denegado, y también puede almacenar un contador de intentos fallidos. Implementos recomendados: ESP32, lector RFID RC522, tarjetas o llaveros RFID, servo SG90 o cerradura eléctrica/solenoide, relé si se usa cerradura de mayor potencia, LEDs, buzzer, botón de salida opcional y sensor magnético de puerta opcional. Tutorial similar: [ESP32 RFID Door Lock with Servo Motor](https://www.youtube.com/watch?v=XywZSvC0xc8)

---

# Entregable mínimo esperado

Cada grupo debe entregar una versión funcional que cumpla con lo siguiente:

1. El microcontrolador lee al menos un sensor.
2. El microcontrolador activa o modifica al menos un actuador.
3. Existe una condición clara que relaciona la medición con la actuación.
4. El sistema muestra datos en monitor serial, pantalla o dashboard.
5. El microcontrolador publica al menos una variable por MQTT usando el broker EMQX.
6. El grupo puede explicar el funcionamiento general del montaje, el código y la comunicación MQTT.

---

# Recomendación final

La prioridad del proyecto no es construir un sistema industrial perfecto, sino demostrar que el grupo puede integrar sensores, actuadores, ESP32 y comunicación MQTT en una solución funcional.

La versión mínima debe funcionar primero de forma local. Luego, el grupo debe agregar la publicación hacia el broker MQTT y, si tiene tiempo, implementar un dashboard o control remoto.
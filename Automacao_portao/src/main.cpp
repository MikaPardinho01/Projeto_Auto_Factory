#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "atuadores.h"

#define mqtt_pub_topic1 "projeto/servo/portao"

unsigned long tempo_anterior = 0;
const unsigned long intervalo = 1000;

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  inicializa_mqtt();
  inicializa_servos();
}

void loop()
{
  atualiza_mqtt();

  if (millis() - tempo_anterior >= intervalo)
  {
    tempo_anterior = millis();
    int angulo = map(analogRead(A0), 0, 4095, 0, 180);
    String json;
    JsonDocument doc;
    doc["PortaoState"] = angulo;
    serializeJson(doc, json);
    publica_mqtt(mqtt_pub_topic1, json);
  }
}
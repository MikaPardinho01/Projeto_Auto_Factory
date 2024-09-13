#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "atuadores.h"

#define mqtt_pub_topic1 "projetoKaue/AutoFactory/Servo/Portao"

unsigned long tempo_anterior = 0;
const unsigned long intervalo = 1000;

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  inicializa_mqtt();
  inicializa_servo();
}

void loop()
{
  atualiza_mqtt();
  rotacao_servo();

  if (millis() - tempo_anterior >= intervalo)
  {
    tempo_anterior = millis();
    String json;
    JsonDocument doc;
    doc["PortaoState"] = estado;
    serializeJson(doc, json);
    publica_mqtt(mqtt_pub_topic1, json);
  }
}
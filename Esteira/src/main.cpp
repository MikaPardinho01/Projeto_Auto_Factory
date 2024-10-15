// *===== BIBLIOTECAS ======
#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "entradas.h"
#include "atuadores.h"

#define mqtt_pub_topic1 "projeto/esteira"

unsigned long tempo_anterior = 0;
const unsigned long intervalo = 1000;

void setup()
{
  Serial.begin(115200);
  inicializa_mqtt();
  inicializa_motor();
}

void loop()
{
  atualiza_mqtt();

  int rotacao = rotacao_motor_passo();
  String json;
  JsonDocument doc;
  doc["Esteira"] = rotacao;
  serializeJson(doc, json);
  publica_mqtt(mqtt_pub_topic1, json);
}

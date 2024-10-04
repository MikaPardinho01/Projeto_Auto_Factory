#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"

#define mqtt_pub_topic1 "projetoKaue/pub/led1"

void acao_botao_externo();

unsigned long tempo_anterior = 0;
const unsigned long intervalo = 1000;

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  inicializa_mqtt();
  inicializa_entradas();
  inicializa_saidas();
}

void loop()
{
  atualiza_saidas();
  atualiza_botoes();
  acao_botao_externo();
  atualiza_mqtt();

  if (millis() - tempo_anterior > intervalo)
  {
    tempo_anterior = millis();

    String json;
    JsonDocument doc;
    doc["LedVeiculos"] = VermelhoState;
    doc["LedVeiculos"] = AmareloState;
    serializeJson(doc, json);
    publica_mqtt(mqtt_pub_topic1, json);
  }
}

void acao_botao_externo()
{
  if (botao_externo_pressionado())
  {
    VermelhoState = !VermelhoState;
    AmareloState = !AmareloState;
    if (VermelhoState && AmareloState)
      publica_mqtt(mqtt_pub_topic1, "LIGADO");
    else
      publica_mqtt(mqtt_pub_topic1, "DESLIGADO");
  }
}

void acao_botao_luz_central()
{
  if (botao_externo_pressionado())
  {
    LuzCentralState = !LuzCentralState;
    if (LuzCentralState)
      publica_mqtt(mqtt_pub_topic1, "LIGADO");
    else
      publica_mqtt(mqtt_pub_topic1, "DESLIGADO");
  }
}
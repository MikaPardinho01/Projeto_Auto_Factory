#include <Arduino.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#define mqtt_topic2 "led6"
#define mqtt_topic1 "led3"

void acao_botao_boot();

void setup() {
  Serial.begin(115200);
  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
  inicializa_mqtt();
}


void loop() {
  atualiza_time();
  atualiza_saidas();
  atualiza_botoes();
  atualiza_mqtt();
  acao_botao_boot();
}

void acao_botao_boot() {
  if (botao_boot_pressionado()) {
    LedBuiltInState = !LedBuiltInState;
    if(LedBuiltInState) publica_mqtt(mqtt_topic1, "Ligado");
    else publica_mqtt(mqtt_topic1, "Desligado");
  }

  else if (botao_boot_pressionado1()) {
   Led_built_InState = !Led_built_InState;
  if(LedBuiltInState) publica_mqtt(mqtt_topic2, "Ligado");
  else publica_mqtt(mqtt_topic2, "Desligado");
  }
}

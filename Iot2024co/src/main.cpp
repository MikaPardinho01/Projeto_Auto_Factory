#include <Arduino.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#include "dht22.h"

#define mqtt_pub_topic1 "temperatura"
#define mqtt_pub_topic2 "umidade"


//* Protótipos das funções do main.cpp

void setup_dht();


void setup()
{
  Serial.begin(115200);
  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
  inicializa_mqtt();
  setup_dht();
}


void loop()
{
  atualiza_time();
  atualiza_saidas();
  atualiza_botoes();
  atualiza_mqtt();
  dht_temperatura();
  dht_umidade();

}
#include <Arduino.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#define LedBuitInPin 2

bool LedBuitInState = LOW;


void setup()
{
  Serial.begin(115200);
  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
}


void loop()
{
  atualiza_time();
  atualiza_saidas();
  botao_boot_pressionado();
}

void inicializa_saidas() {
    pinMode(LedBuitInPin, OUTPUT);
}

void atualiza_saidas() {
    digitalWrite(LedBuitInPin, LedBuitInState);
        // ? Verifica se o botao_boot foi pressionado
    if(botao_boot_pressionado) {
        Serial.println("Botao pressionado");
        LedBuitInState = !LedBuitInState;
    }
    // ? Verifica se o botao_boot foi solto
    else if (botao_boot_pressionado) {
        Serial.println("Botao solto");
    }
}




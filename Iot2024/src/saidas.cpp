#include <Arduino.h>
#include "saidas.h"
#define LedBuitInPin 2

bool LedBuitInState = LOW;

void inicializa_saidas() {
    pinMode(LedBuitInPin, OUTPUT);
}

void atualiza_saidas() {
    digitalWrite(LedBuitInPin, LedBuitInState);
}

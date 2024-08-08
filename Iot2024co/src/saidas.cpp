#include <Arduino.h>
#include "saidas.h"
#define LedBuiltInPin 2
#define Led_buils 25

bool LedBuiltInState = LOW;
bool Led_built_InState = LOW;

void inicializa_saidas() {
    pinMode(LedBuiltInPin, OUTPUT);
    pinMode(Led_buils, OUTPUT);
}

void atualiza_saidas() {
    digitalWrite(LedBuiltInPin, LedBuiltInState);
    digitalWrite(Led_buils, Led_built_InState);
}
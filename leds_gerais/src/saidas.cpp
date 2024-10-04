#include <Arduino.h>
#include "saidas.h"

#define Vermelho_pin 26
#define Amarelo_pin  25
#define luzCentral 15

bool VermelhoState = LOW;
bool AmareloState = LOW;
bool LuzCentralState = LOW;

void inicializa_saidas()
{
    pinMode(Vermelho_pin, OUTPUT);
    pinMode(Amarelo_pin, OUTPUT);
    pinMode(luzCentral, OUTPUT);
}

void atualiza_saidas()
{
    digitalWrite(Vermelho_pin, VermelhoState);
    digitalWrite(Amarelo_pin, AmareloState);
    digitalWrite(luzCentral, LuzCentralState);
}
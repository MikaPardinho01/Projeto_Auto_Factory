#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

#define BOTAO_EXTERNO_PIN 12

Bounce botaoExterno = Bounce();

void inicializa_entradas()
{
    botaoExterno.attach(BOTAO_EXTERNO_PIN, INPUT_PULLUP);
}

// Atualiza o estado dos botões
void atualiza_botoes()
{
    botaoExterno.update();
}

bool botao_externo_pressionado()
{
    return botaoExterno.fell();
}
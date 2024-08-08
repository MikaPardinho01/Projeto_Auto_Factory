#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"

#define BOTAO_BOOT_PIN 0
#define BOTAO_BOOT_outside 12


Bounce botao_boot = Bounce();
Bounce botao_boot01 = Bounce();

void inicializa_entradas() {
    botao_boot.attach(BOTAO_BOOT_PIN, INPUT_PULLUP);
    botao_boot01.attach(BOTAO_BOOT_outside, INPUT_PULLUP);
}

void atualiza_botoes() {
    //atualiza do estado do botao
    botao_boot.update();
    botao_boot01.update();
}


bool botao_boot_pressionado() {
    return botao_boot.fell();
}
bool botao_boot_pressionado1() {
    return botao_boot01.fell();
}
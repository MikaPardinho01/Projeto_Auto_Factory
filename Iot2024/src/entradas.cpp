#include <Arduino.h>
#include <Bounce2.h>
#include <entradas.h>
#include <saidas.h>

#define BOTAO_BOOT_PIN 0
Bounce botao_boot = Bounce();

void inicializa_entradas() {
    botao_boot.attach(BOTAO_BOOT_PIN, INPUT_PULLUP);
}

void atualiza_botoes() {
    // ? Atualiza o estado do botao_boot
    botao_boot.update();
}

/*@brief Indica se o botão boot foi pressionado
@return bool (retorna verdadeiro caso foi pressionado)
*/

bool botao_boot_pressionado() {
    return botao_boot.fell();
}
#include <Arduino.h>
#include <Servo.h>
#include "atuadores.h"
#include <Bounce2.h>

#define pinServo 15
#define pinBotao 12

Bounce botao = Bounce();
Servo spinning;

bool ativacao = false;
bool servoInicio = false;
bool estado = false;
void inicializa_servo()
{

  botao.attach(pinBotao, INPUT_PULLUP);
  spinning.attach(pinServo);
  spinning.write(pinServo, 90);
  delay(500);
  servoInicio = true;
}

int rotacao_servo()
{
  botao.update();
  if (botao.changed() && botao.read() == HIGH)
  {
    ativacao = !ativacao;
    if (ativacao)
    {
      spinning.write(pinServo, 90);
      delay(50);
      estado = 1;
    }
    else
    {
      spinning.write(pinServo, 0);
      delay(50);
      estado = 0;
    }
  }
  return estado;
}

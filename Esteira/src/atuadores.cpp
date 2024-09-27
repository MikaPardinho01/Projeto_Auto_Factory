#include <Arduino.h>
#include <Stepper.h>
#include "atuadores.h" // incluir motor de passo

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

const int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void inicializa_motor()
{
  myStepper.setSpeed(30);
}

bool rotacao_motor()
{
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempo_anterior >= intervalo)
  {
    tempo_anterior = tempoAtual;
    myStepper.step(stepsPerRevolution);
    return true;
  }
  return false;
}
#include <ESP32Servo.h>
#include "atuadores.h"
#include <Stepper.h> // incluir motor de passo

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

bool motorLigado = false;
int passoAtual = 0;

const int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void inicializa_motor()
{
  myStepper.setSpeed(5);
}

/*void rotacao_motor()
{
  unsigned long currentMillis = millis(); // obtém o tempo atual em milissegundos

  if (currentMillis - previousMillis >= interval)
  {
    // salva o tempo atual
    previousMillis = currentMillis;

    // passo uma revolução em uma direção:
    Serial.println("sentido_horário");
    myStepper.step(stepsPerRevolution);
  }
}*/

//--------------------------------------------

void acionarBobinas(int passo)
{
  switch (passo)
  {
  case 0:
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    break;
  case 1:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    break;
  case 2:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    break;
  case 3:
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    break;
  }
}

int rotacao_motor_passo()
{
  if (motorLigado)
  {
    passoAtual = (passoAtual + 1) % 4;
    acionarBobinas(passoAtual);
    delay(5);
  }
}
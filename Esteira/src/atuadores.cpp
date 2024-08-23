#include <ESP32Servo.h>
#include "atuadores.h"
#include <Stepper.h> // incluir motor de passo


#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

const int stepsPerRevolution = 2048;


Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void inicializa_motor()
{
  myStepper.setSpeed(5);
}

void rotacao_motor()
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
}
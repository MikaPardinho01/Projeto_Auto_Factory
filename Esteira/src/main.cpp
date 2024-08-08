// *===== BIBLIOTECAS ======
#include <Arduino.h>
#include <Stepper.h> // incluir motor de passo

const int stepsPerRevolution = 2048;  // é o número de passos que um motor de passo deve dar para completar uma volta completa de 360 graus.

// *===== DEFINICOES ======
// Pins setados no motor de passo
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// *===== OBJETOS ========
// inicializar a biblioteca do motor (stepper)
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void setup() 
{
  // define a velocidade em 5 rpm (é uma medida de quantas voltas completas um objeto ou motor faz em um minuto.)
  myStepper.setSpeed(5);
  Serial.begin(115200);
}

void loop() 
{
  // passo uma revolução em uma direção:
  Serial.println("sentido_horário");
  myStepper.step(stepsPerRevolution);
  delay(1000);
}
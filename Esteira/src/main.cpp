// *===== BIBLIOTECAS ======
#include <Arduino.h>
#include <Stepper.h> // incluir motor de passo

const int stepsPerRevolution = 2048; // é o número de passos que um motor de passo deve dar para completar uma volta completa de 360 graus.
#define mqtt_pub_topic1 "projetoKaue/AutoFactory/Esteira"

// *===== DEFINICOES ======
// Pins setados no motor de passo
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// *===== OBJETOS ========
// inicializar a biblioteca do motor (stepper)

void setup()
{
  Serial.begin(115200);
  inicializa_motor();
}

void loop()
{
  unsigned long currentMillis = millis(); // obtém o tempo atual em milissegundos

  if (currentMillis - previousMillis >= Intervalo)
  {
    // salva o tempo atual
    previousMillis = currentMillis;

    // passo uma revolução em uma direção:
    Serial.println("sentido_horário");
    myStepper.step(stepsPerRevolution);
  }
}
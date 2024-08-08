#include <Arduino.h>
#include <Servo.h>
#include <Bounce2.h>

#define pinServo 15
#define pinBotao 22

Servo spinning;
Bounce botao = Bounce();

bool ativacao = false;
bool servoInicio = false;

void setup()
{
  botao.attach(pinBotao, INPUT_PULLUP);

  Serial.begin(9600);
  spinning.attach(pinServo);

  spinning.write(pinServo, 90); 
  delay(500);
  servoInicio = true;
}

void loop()
{
  botao.update();
  if (botao.changed() && botao.read() == HIGH) 
  {
    ativacao = !ativacao; 
    if (ativacao)
    {
      spinning.write(pinServo, 90); 
      delay(50);
    }
    else
    {
      spinning.write(pinServo, 0); 
      delay(50);
    }
  }
}
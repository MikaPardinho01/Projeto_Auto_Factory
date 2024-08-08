#include <Arduino.h>

int Vermelho_pin = 21;
int Amarelo_pin = 22;
int Vermelho2_pin = 23;
int Amarelo2_pin = 2;

void setup()
{
pinMode(Vermelho_pin, OUTPUT);
pinMode(Amarelo_pin, OUTPUT);
pinMode(Vermelho2_pin, OUTPUT);
pinMode(Amarelo2_pin, OUTPUT);
}

void loop()
{
  digitalWrite(Vermelho_pin, HIGH);
  digitalWrite(Vermelho2_pin, HIGH);
  digitalWrite(Amarelo_pin, LOW);
  pinMode(Amarelo2_pin, LOW);
  delay(2000); 
  digitalWrite(Vermelho_pin, LOW);
  digitalWrite(Vermelho2_pin, LOW);
  digitalWrite(Amarelo_pin, HIGH);
  pinMode(Amarelo2_pin, HIGH);
  delay(2000);
}
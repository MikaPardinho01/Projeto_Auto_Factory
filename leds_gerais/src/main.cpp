#include <Arduino.h>
#include <Bounce2.h>

const int Vermelho_pin = 15;
const int Amarelo_pin = 2;
const int luzCentral = 4; 
const int botao = 19; 

bool estado_botao = LOW;
Bounce debouncer = Bounce();

void setup()
{
pinMode(Vermelho_pin, OUTPUT);
pinMode(Amarelo_pin, OUTPUT);
pinMode(luzCentral, OUTPUT);
pinMode(botao, INPUT_PULLUP);
debouncer.attach(botao);
debouncer.interval(10);
}

void loop()
{

  digitalWrite(Vermelho_pin, HIGH);
  digitalWrite(Amarelo_pin, LOW);
  delay(500);  
  digitalWrite(Vermelho_pin, LOW);
  digitalWrite(Amarelo_pin, HIGH);
  delay(500);

  //debouncer.update();
  //if (debouncer.fell()){
  //estado_botao = !estado_botao;
  //digitalWrite(luzCentral, estado_botao);
  digitalWrite(luzCentral, HIGH);
}
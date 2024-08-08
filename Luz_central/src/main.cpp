#include <Arduino.h>
#include <Bounce2.h>

const int luzCentral = 4; 
const int botao = 19; 

bool estado_botao = LOW;

void setup() {
  
  pinMode(luzCentral, OUTPUT);
  
  pinMode(botao, INPUT);
}

void loop() 
{
  if (digitalRead(botao) == HIGH) 
  {
      estado_botao = !estado_botao;
    
     digitalWrite(luzCentral, estado_botao);
    
  }
}
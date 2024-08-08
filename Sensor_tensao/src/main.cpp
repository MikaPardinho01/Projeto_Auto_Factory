//*=== BIBLIOTECAS ===
#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

//*=== DEFINICOES ===

#define sinalSensor 15 // Pino em que o sensor esta pinado 

//*=== OBJETOS ===
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

//*=== VARIAVEIS ===
float tensaoSensor; // variavel que recebe a variacao da tensao do sensor

void setup() 
{
 u8g2.begin(); // inicia display
 Serial.begin(9600);
 Serial.print(tensaoSensor); // aparecer no serial o valor recebido da tensao do sensor
}

void loop() 
{
 tensaoSensor = analogRead(sinalSensor) * (25.00/1023.00); // parte essencial, 25.000 por conta que 25 e a tensao maxima recebida pelo sensor, e dividido por 1023 para o calculo gerar o valor certo recebido pelo sensor.
 u8g2.setFont(u8g2_font_mystery_quest_24_tf);
 u8g2.clearDisplay();
 u8g2.setCursor(0, 13);
 u8g2.println("       TENSAO");
 u8g2.setCursor(0, 45);
 u8g2.print("     ");
 u8g2.print(tensaoSensor);
 u8g2.print(" V");
 u8g2.sendBuffer();
 delay(20);
}
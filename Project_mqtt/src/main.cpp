#include <Arduino.h>
#include <iot.h>


void setup() {
  Serial.begin(115200);
  setup_time();
  setup_wifi();
}

void loop() {
  atualiza_time();
  hora_certa();
}
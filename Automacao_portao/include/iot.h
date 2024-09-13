#pragma once
#include <ArduinoJson.h> 

void tratar_msg(char *topic, JsonDocument &doc);

void setup_wifi();
void inicializa_mqtt();

void publica_mqtt(String topico, String msg);

void atualiza_mqtt();

extern bool estado;
extern int rotacao_servo();
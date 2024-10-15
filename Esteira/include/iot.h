#pragma once

//Inicia a conexão MQTT
void inicializa_mqtt();

void publica_mqtt(String topico, String msg);

//Atualiza a conexão MQTT
void atualiza_mqtt();

extern bool motorLigado;
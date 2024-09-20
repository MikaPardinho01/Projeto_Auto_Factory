#pragma once

void setup_wifi();

void inicializa_mqtt();

void publica_mqtt(String topico, String msg);

void atualiza_mqtt();

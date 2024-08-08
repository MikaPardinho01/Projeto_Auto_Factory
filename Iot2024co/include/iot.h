#pragma once

//Inicia a conexão WiFi
void setup_wifi();
void inicializa_mqtt();
void publica_mqtt(String topico, String msg);
void publica_mqtt(String topico, String msgm);
void atualiza_mqtt();

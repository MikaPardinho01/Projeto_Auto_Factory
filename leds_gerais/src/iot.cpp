#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "senhas.h"
#include "saidas.h"

// Definição dos tópicos de inscrição
#define mqtt_topic1 "projetoKaue/led1"
// Definição do ID do cliente MQTT randomico
const String cliente_id = "ESP32Clientd" + String(random(0xffff), HEX);
// Protótipos das funçõesWiFiClientSecure espClient;
WiFiClient espClient;
PubSubClient client(espClient);



void tratar_msg(char *topic, String msg);
void callback(char *topic, byte *payload, unsigned int length);
void reconecta_mqtt();
void inscricao_topicos();

// Inicia a conexão WiFi
void setup_wifi()
{
    Serial.println();
    Serial.print("Conectando-se a Rede WiFi ");
    Serial.print(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Conectado ao WiFi com sucesso com IP: ");
    Serial.println(WiFi.localIP());
}

// Atualiza a conexão MQTT
void inicializa_mqtt()
{
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void atualiza_mqtt()
{
    client.loop();
    if (!client.connected()) // Corrigido: use `!client.connected()` em vez de `client.state() != MQTT_CONNECTED`
    {
        reconecta_mqtt();
    }
}

// Função de callback chamada quando uma mensagem é recebida
void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.printf("Mensagem recebida [ %s ] \n\r", topic);
    String msg = "";
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
        msg += (char)payload[i];
    }
    Serial.println();
    tratar_msg(topic, msg);
}

// Função de reconexão ao Broker MQTT
void reconecta_mqtt()
{
    while (!client.connected())
    {
        Serial.print("Tentando se conectar ao Broker MQTT: ");
        Serial.println(mqtt_server);
        if (client.connect(cliente_id.c_str()))
        {
            Serial.println("Conectado ao Broker MQTT");
            inscricao_topicos();
        }
        else
        {
            Serial.println("Falha ao conectar ao Broker.");
            Serial.println("Havera nova tentativa de conexao em 2 segundos");
            delay(2000);
        }
    }
}
// Publica uma mensagem no tópico MQTT
void publica_mqtt(String topico, String msg)
{
    client.publish(topico.c_str(), msg.c_str());
}

//!----------------------------------------
// TODO Alterar a programação apartir daui
//!----------------------------------------

// Inscreve nos tópicos MQTT
void inscricao_topicos()
{
    client.subscribe(mqtt_topic1); // LED 1
}

// Trata as mensagens recebidas
void tratar_msg(char *topic, String msg)
{
    if (strcmp(topic, mqtt_topic1) == 0)
    {
        JsonDocument doc;
        deserializeJson(doc, msg);
        bool VermelhoState = doc["LedVeiculos"];
        bool AmareloState = doc["LedVeiculos"];

        if (VermelhoState && AmareloState)
        {
            VermelhoState = true;
            AmareloState = true;
        }
        else if (!VermelhoState && !AmareloState)
        {
            VermelhoState = false;
            AmareloState = false;
        }
        else if (msg == "alterna")
        {
            VermelhoState = !VermelhoState;
            AmareloState = !AmareloState;
        }
    }
}

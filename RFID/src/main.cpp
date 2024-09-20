//*----------------------------
//* RST/Reset   RST          02 //pode alterar
//* SPI SS      SDA(SS)      05 //pode alterar
//* SPI MOSI    MOSI         23
//* SPI MISO    MISO         19
//* SPI SCK     SCK          18
 /*----------------------------

//**Bibliotecas*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <U8g2lib.h>
#include "senhas.h"

//* Definição dos tópicos de inscrição */
#define mqtt_topic1 "Projeto/RFID"

//* Definição do ID do cliente MQTT randomico */
const String cliente_id = "ESP32Client" + String(random(0xffff), HEX);

//* Definição dos dados de conexão */
WiFiClient espClient;
PubSubClient client(espClient);

//* Protótipos das funções */
void tratar_msg(char *topic, String msg);
void callback(char *topic, byte *payload, unsigned int length);
void reconecta_mqtt();
void inscricao_topicos();

//* Inicia a conexão WiFi */
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

//* Inicia a conexão MQTT */
void inicializa_mqtt()
{
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void atualiza_mqtt()
{
  client.loop();
  if (!client.connected())
  {
    reconecta_mqtt();
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  // Serial.printf("Mensagem recebida [ %s ] \n\r", topic);
  String msg = "";
  for (int i = 0; i < length; i++)
  {
    // Serial.print((char)payload[i]);
    msg += (char)payload[i];
  }
  // Serial.println();
  tratar_msg(topic, msg);
}

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

void publica_mqtt(String topico, String msg)
{
  client.publish(topico.c_str(), msg.c_str());
}

void inscricao_topicos()
{
  client.subscribe(mqtt_topic1);
}

//**Definições*/
#define SS_PIN 5
#define RST_PIN 2
#define DEBUG false
#define UID1 669071206
#define UID3 340843683

int mensagem = 0;

//**Objetos*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
MFRC522 mfrc522(SS_PIN, RST_PIN); // Criar instância do MFRC522

//*Prototipos**/
unsigned long lerRFID(void);
// void enviarJson(unsigned long uid, const char* status, const char* mensagem);

//**Configuração*/
void setup()
{
  u8g2.begin();
  Serial.begin(9600); // Iniciar comunicação serial
  SPI.begin();        // Iniciar SPI
  mfrc522.PCD_Init(); // Iniciar MFRC522
  setup_wifi();
  inicializa_mqtt();
}

void loop()
{
  unsigned long uid = lerRFID();

  if (DEBUG)
  {
    Serial.println("Aproxime o cartão do leitor");
    if (uid == 0){
      Serial.println("Cartão não encontrado");
    }
    if (uid == 1){
      Serial.println("Erro ao ler cartão");
    }
  }

  if (uid > 1){
    Serial.print("UID: ");
    Serial.println(uid);

    switch (uid){
    case UID1:
      Serial.println("Tag 1");

      // u8g2.clearBuffer();
      // u8g2.drawRFrame(0, 0, 126, 62, 2); 
      // u8g2.setFont(u8g2_font_efraneextracondensed_te);
      // u8g2.drawStr(15, 25, "Tag cadastrada");
      // u8g2.sendBuffer();

      // enviarJson(uid, "Tag cadastrada", "Tag 1");
      break;

    case UID3:
      Serial.println("Tag 2");
      u8g2.clearBuffer();
      u8g2.drawRFrame(0, 0, 126, 62, 2); 
      u8g2.setFont(u8g2_font_efraneextracondensed_te);
      u8g2.drawStr(15, 25, "Tag 2 cadastrada");
      u8g2.sendBuffer();

    // enviarJson(uid, "Tag 2 cadastrada", "Tag 2");
    break;

    default:
      u8g2.clearBuffer();
      u8g2.drawRFrame(0, 0, 126, 62, 2); 
      u8g2.setFont(u8g2_font_efraneextracondensed_te);
      u8g2.drawStr(15, 25, "Tag não cadastrada" );
      u8g2.sendBuffer();
      // enviarJson(uid, "Acesso negado", "Tag não cadastrada");
      break;
    }
  }

  delay(1000); //!NAO USE DELAY EM HIPITESE ALGUMA
}

unsigned long lerRFID()
{
  // Procura por cartões RFID
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return 0;
  }

  // Seleciona um dos cartões
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return 1;
  }

  unsigned long numericUID = 0;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    numericUID = numericUID * 256 + mfrc522.uid.uidByte[i];
  }

  return numericUID;
}
// void enviarJson(unsigned long uid, const char* status, const char* mensagem)
// {
//   JsonDocument doc;
//   doc["UID"] = uid;
//   doc["status"] = status;
//   doc["mensagem"] = mensagem;

  
//   String jsonString;
//   serializeJson(doc, jsonString);

  
//   Serial.println(jsonString);
// }

void tratar_msg(char *topic, String msg)
{ 
  if (strcmp(topic, mqtt_topic1) == 0)
  {
    
    
  }
}

void json(){
  JsonDocument doc;
  doc["UID"] = UID1;
  doc["status"] = "Tag 1";
  doc["mensagem"] = mensagem ;
}
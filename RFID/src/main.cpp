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
#define mqtt_topic1 ""

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

//**Definições*/
#define SS_PIN 5
#define RST_PIN 2
#define DEBUG false
#define UID1 669071206
#define UID3 3488487708

#define servo 21

//**Objetos*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
MFRC522 mfrc522(SS_PIN, RST_PIN); // Criar instância do MFRC522
Servo servoMotor = Servo();

//*Prototipos**/
unsigned long lerRFID(void);
void enviarJson(unsigned long uid, const char* status, const char* mensagem);

//**Configuração*/
void setup()
{
  u8g2.begin();
  Serial.begin(9600); // Iniciar comunicação serial
  SPI.begin();        // Iniciar SPI
  mfrc522.PCD_Init(); // Iniciar MFRC522
  servoMotor.attach(servo); //Iniciar o Servo
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
      Serial.println("Cartão 1");
      u8g2.clearBuffer();
      u8g2.drawRFrame(0, 0, 126, 62, 2); 
      u8g2.setFont(u8g2_font_efraneextracondensed_te);
      u8g2.drawStr(15, 25, "Acesso liberado");
      u8g2.sendBuffer();

      servoMotor.write(servo, 90);
      enviarJson(uid, "Acesso liberado", "Cartão 1");
      break;

    case UID3:
      Serial.println("Cartão 3");
      u8g2.clearBuffer();
      u8g2.drawRFrame(0, 0, 126, 62, 2); 
      u8g2.setFont(u8g2_font_efraneextracondensed_te);
      u8g2.drawStr(15, 25, "Acesso liberado");
      u8g2.sendBuffer();

    servoMotor.write(servo, 0);
    enviarJson(uid, "Acesso liberado", "Cartão 3");
    break;

    default:
      u8g2.clearBuffer();
      u8g2.drawRFrame(0, 0, 126, 62, 2); 
      u8g2.setFont(u8g2_font_efraneextracondensed_te);
      u8g2.drawStr(15, 25, "cartão não cadastrado");
      u8g2.sendBuffer();
      enviarJson(uid, "Acesso negado", "Cartão não cadastrado");
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
void enviarJson(unsigned long uid, const char* status, const char* mensagem)
{
  JsonDocument doc;
  doc["UID"] = uid;
  doc["status"] = status;
  doc["mensagem"] = mensagem;

  // Serialize the JSON document to a string
  String jsonString;
  serializeJson(doc, jsonString);

  // Send the JSON string over the Serial
  Serial.println(jsonString);
}
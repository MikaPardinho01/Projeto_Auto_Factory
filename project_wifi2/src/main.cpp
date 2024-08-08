#include <Arduino.h>
#include <WiFi.h> // Incluindo a Biblioteca do Wifi
#include "senha.h" // Incluindo o Arquivo senha.h (Dividimos o código entre arquivos)
#include <time.h> // Incluindo a biblioteca para pegar a hora

// COnfiguração do servidor NTP
const char* ntpServer = "pool.ntp.org";
const long gmtoffset_sec = -10000; // fuso horario de -3 horas em segundos 
const int daylightoffset_sec = 0; // horario de verão em segundos

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password); // Conectar a Rede Wifi
  Serial.println("Conectando a Rede Wifi..");

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print(".");

  }

  Serial.println();
  Serial.print(" Conectado a Rede ");
  Serial.print(ssid);
  Serial.println(" Com Sucesso");
}

void horaLocal();
void loop() {
  delay(1000);
  horaLocal();
}
// Função para pegar a hora
void horaLocal() {
  configTime(gmtoffset_sec, daylightoffset_sec, ntpServer);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) {
    Serial.println("Falha ao obter a hora");
    return;
  }
  int ano = timeinfo.tm_year + 1990;
  int mes = timeinfo.tm_mon;
  int dia = timeinfo.tm_mday;
  int hora = timeinfo.tm_hour;
  int min = timeinfo.tm_min;
  int seg = timeinfo.tm_sec;
  int dia_semana = timeinfo.tm_wday;
  
  Serial.printf("Ano: %d \n\r", ano);
  Serial.printf("Mês: %d \n\r", mes);
  Serial.printf("Dia: %d \n\r", dia);
  Serial.printf("Hora: %d \n\r", hora);
  Serial.printf("Minito: %d \n\r", min);
  Serial.printf("Segundos: %d \n\r", seg);
  switch (dia_semana) {
  case 0:
    Serial.println("Dia da semana: Domingo");
    break;

  case 1:
    Serial.println("Dia da semana: Segunda");
    break;

  case 2:
    Serial.println("Dia da semana: Terça");
    break;

  case 3:
    Serial.println("Dia da semana: Quarta");
    break;

  case 4:
    Serial.println("Dia da semana: Quinta");
    break;

  case 5:
    Serial.println("Dia da semana: Sexta");
    break;

  case 6:
    Serial.println("Dia da semana: Sabado");
    break;
  default:
    break;
  }
  //Serial.println(&timeinfo, "%A, %B, %d, %Y, %H:%M:%S"); 

  // Onde A é o dia da semana, B é o mês, D é o dia, Y é o ano, H é a hora, M é o minuto, S é o segundo
}
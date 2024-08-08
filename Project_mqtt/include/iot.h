#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>


const int fusoHorario = -10800;
const unsigned long atualizaNTP = 60000;


void setup_wifi();
void hora_certa();
unsigned long timeStamp();
void atualiza_time();
void setup_time();
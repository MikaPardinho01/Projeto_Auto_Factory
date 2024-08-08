#include <Arduino.h>
#include <iot.h>
#include <senhas.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", fusoHorario, atualizaNTP);

void setup_wifi() {
    //Serial.printf("Conectando-se a Rede Wifi %s \n\r", ssid);
    WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    Serial.println();
    Serial.print("Conectado ao WiFi com sucesso no IP: ");
    Serial.println(WiFi.localIP());
}

void hora_certa(){
    unsigned long epochTime = timeClient.getEpochTime();      
    //Serial.println(epochTime);
    setTime(epochTime);
    /*hour(); minute(); second();
    day(); month(); year(); weekday();*/
    Serial.printf("%02d:%02d:%02d * %02d/%02D/%04d \n", hour(), minute(), second(), day(), month(), year());
}

unsigned long timeStamp() {
    return timeClient.getEpochTime();
}

void setup_time() {
    timeClient.begin();
}

void atualiza_time() {
    timeClient.update();
}
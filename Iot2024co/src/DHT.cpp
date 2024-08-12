#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "iot.h"
#include "dht.h"

#define mqtt_pub_topic1 "temperatura"
#define mqtt_pub_topic2 "umidade"

#define DHTPIN 19  //* Define o pino ao qual o sensor DHT está conectado
#define DHTTYPE DHT22  //* Define o tipo de sensor DHT utilizado

DHT dht(DHTPIN, DHTTYPE);  //* Cria o objeto sensor DHT


void setup_dht(){

    dht.begin(); //* Inicializa o DHT
}

void dht_temperatura() {

   float temperature = dht.readTemperature();

    if (!isnan(temperature)) {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" *C");

    publica_mqtt(mqtt_pub_topic1, String(temperature));
    
    }
}


void dht_umidade() {

    float humidity = dht.readHumidity();

    if (!isnan(humidity)) {
    Serial.print("Umidade: ");
    Serial.print(humidity);
    Serial.println(" %"); 

    publica_mqtt(mqtt_pub_topic2, String(humidity));
    
  }
  } 
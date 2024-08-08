#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "dht.h"

#define DHTPIN 19 
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);  


void setup_dht() {
    dht.begin();   
}

void dht_temperatura() {
   float temperature = dht.readTemperature();
    if (!isnan(temperature)) {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" *C");
    String temp_str = String(temperature);
    publica_mqtt(mqtt_temp_topic, temp_str.c_str()); 
    }
}


void dht_umidade() {
    float humidity = dht.readHumidity();
    if (!isnan(humidity)) {
    Serial.print("Umidade: ");
    Serial.print(humidity);
    Serial.println(" %"); 
    String hum_str = String(humidity);
    publica_mqtt(mqtt_hum_topic, hum_str.c_str());
  }
} 







//
// Created by llewe on 18.02.24.
//
#include <ArduinoHA.h>
#include <DHT.h>

#include "mqttClient.h"

#include "config.h"

#include "secrets.h"
DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen

HADevice mqttDevice;
HAMqtt mqtt(wifiClient, mqttDevice);

HASensor sensorHumid("humidity");
HASensor sensorTemp("temp");

HAFan fan("my_fan2", HAFan::SpeedsFeature);

unsigned long previousMillis = 0;
const long interval = 2000;


int last_speed_value = 0;
int current_speed_value = 0;

void setSpeed(uint16_t speed){
    // Map the percentage (0-100) to PWM range (0-1023)
    int pwmValue = map(speed, 0, 100, 0, 1023);
    analogWrite(FAN_PIN, pwmValue);

}

void sendTempUpdate() {

    Serial.println("Read DHT22 sensor data");
    float humidity = dht.readHumidity();
    float temp = dht.readTemperature();

    if (isnan(humidity) || isnan(temp)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" *C");
    sensorHumid.setValue(String(humidity).c_str());
    sensorTemp.setValue(String(temp).c_str());
}


void onStateCommand(bool state, HAFan* sender) {
    if(state==0){
        current_speed_value=0;
    }else{
        current_speed_value=last_speed_value;
    }
    setSpeed(current_speed_value);

    sender->setState(state); // report state back to the Home Assistant
    sender->setSpeed(current_speed_value);
}

void onSpeedCommand(uint16_t speed, HAFan* sender) {
    last_speed_value = speed;
    setSpeed(speed);


    sender->setState(speed != 0); // update state
    sender->setSpeed(speed); // report speed back to the Home Assistant
}



void mqttSetup() {
    Serial.println("Setting up MQTT client");

    mqttDevice.setUniqueId(mac, sizeof(mac));

    mqttDevice.setName(DEVICE_NAME);
    mqttDevice.setModel("NodeMCU");
    mqttDevice.setManufacturer(MANIFAUCTURER);

    mqttDevice.enableSharedAvailability();
    mqttDevice.enableLastWill();

    fan.setSpeedRangeMin(1);
    fan.setSpeedRangeMax(100);

    fan.onStateCommand(onStateCommand);
    fan.onSpeedCommand(onSpeedCommand);

    fan.setAvailability(true);

    sensorHumid.setIcon("mdi:water-percent");
    sensorHumid.setName("Humidity");
    sensorHumid.setUnitOfMeasurement("%");

    sensorTemp.setIcon("mdi:thermometer");
    sensorTemp.setName("Temperature");
    sensorTemp.setUnitOfMeasurement("°C");

    Serial.println("Setting up MQTT client");

    mqtt.begin(MQTT_SERVER,MQTT_PORT, MQTT_USER, MQTT_PASSWORD);
    Serial.println("MQTT client setup done");

    dht.begin();
}

void mqttLoop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {

        previousMillis = currentMillis;
        sendTempUpdate();
    }

    mqtt.loop();
}
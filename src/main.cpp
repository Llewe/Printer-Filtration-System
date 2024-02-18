#include <Arduino.h>
#include "wifi.h"
#include "mqttClient.h"

void setup() {
    Serial.begin(9600);         // Initialize the Serial interface with 115200 baud rate
    Serial.println("");
    Serial.println("Start Setup");  // Print the "Hello, world!" to the Serial interface
    pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

    setupWifi();
    mqttSetup();

    Serial.println("End Setup");  // Print the "Hello, world!" to the Serial interface
}

// the loop function runs over and over again forever
void loop() {
    mqttLoop();

}
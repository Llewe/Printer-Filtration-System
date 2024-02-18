//
// Created by llewe on 18.02.24.
//
#include <ESP8266WiFi.h>
#include <ArduinoHA.h>

#include "wifi.h"

#include "secrets.h"

WiFiClient wifiClient;

void setupWifi() {

    WiFi.macAddress(mac);

    // you can skip this part if you're already maintaining the connection logic
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500); // waiting for the connection
    }
}
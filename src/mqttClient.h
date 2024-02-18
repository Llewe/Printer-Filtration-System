//
// Created by llewe on 18.02.24.
//
#pragma once

#include <ESP8266WiFi.h>


extern byte mac[WL_MAC_ADDR_LENGTH];
extern WiFiClient wifiClient;

void mqttSetup();

void mqttLoop();
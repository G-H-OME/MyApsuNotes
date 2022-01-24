/*
  Wifi.cpp - Simple example on connecting wifi ---ESP32
  by sicko
  */
#include "Wifi.h"
#include <Arduino.h>
#include <WiFi.h>
void Wifi_connect(const char *ssid, const char *passwd)
{
  Serial.println("wifi---Connecting to ");
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi connecting");
    delay(1000);
  }
  Serial.println("wifi --Connected");
}
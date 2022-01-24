/*
  Wifi.cpp - Simple example on OTA update---ESP32
  by sicko
  */
#include "Esp32httpOta.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include "ESP32httpUpdate.h"
void Ota_update(String host)
{

  Serial.println("Starting Update");
  t_httpUpdate_return ret = ESPhttpUpdate.update(host);
  switch (ret)
  {
  case HTTP_UPDATE_FAILED:
    Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
    break;

  case HTTP_UPDATE_NO_UPDATES:
    Serial.println("HTTP_UPDATE_NO_UPDATES");
    break;

  case HTTP_UPDATE_OK:
    Serial.println("HTTP_UPDATE_OK");
    break;
  }
}
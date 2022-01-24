
#include <Arduino.h>
#include <WiFi.h>
#include "Wifi.h"
#include "PubSubClient.h"
#include "Esp32httpOta.h"
#include <HTTPClient.h>

void Mqtt_connect(const char *mqtt_host, const int mqtt_port, const char *username, const char *passwd);
void Mqtt_sub(const char *topic);
void Mqtt_pub(const char *topic, const char *message);
void Mqtt_loop();


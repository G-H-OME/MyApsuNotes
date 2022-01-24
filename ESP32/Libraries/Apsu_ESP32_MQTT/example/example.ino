#include <Arduino.h>
#include <WiFi.h>
#include "Mqtt.h"
#include "Esp32httpOta.h"
const char *mqtt_broker = "192.168.50.180";
const char *topic = "ota";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *SSID = "apsu";
const char *PSWD = "yangpaopao";

/*
  修改callback
 */
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message:");
  payload[length] = '\0';
  // 以字符串形式打印出来
  Serial.println((char *)payload);
  // OTA升级，勿动！！
  if ((String((char *)payload).indexOf(".bin")) > 0)
  {
    Ota_update(String((char *)payload));
  }
}
void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID, PSWD);
  // callback参数为可选
  // Mqtt_connect(mqtt_broker, mqtt_port, mqtt_username, mqtt_password)
  Mqtt_connect(mqtt_broker, mqtt_port, mqtt_username, mqtt_password, callback);
  Mqtt_sub(topic);
  Mqtt_pub(topic, "来了来了来了");
}

void loop()
{
  Mqtt_loop();
}
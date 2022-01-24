/*
  Mqtt.cpp - Simple example on OTA update---ESP32
  by sicko
  */
#include "Mqtt.h"

WiFiClient esp32_client;
PubSubClient client(esp32_client);
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message:");
  payload[length] = '\0';
  Serial.println((char *)payload);

  if ((String((char *)payload).indexOf(".bin")) > 0)
  {
    Ota_update(String((char *)payload));
  }
}

void Mqtt_connect(const char *mqtt_host, const int mqtt_port, const char *username, const char *passwd)
{
  client.setServer(mqtt_host, mqtt_port);
  client.setCallback(callback);
  while (!client.connected())
  {
    String client_id = "";
    Serial.println("client is connecting");
    if (client.connect(client_id.c_str(), username, passwd))
    {
      Serial.println("BBBBroker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void Mqtt_sub(const char *topic)
{
  client.subscribe(topic);
}

void Mqtt_pub(const char *topic, const char *message)
{
  client.publish(topic, message);
}

void Mqtt_loop()
{
  client.loop();
}

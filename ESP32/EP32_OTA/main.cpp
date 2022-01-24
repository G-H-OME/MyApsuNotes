#include <Arduino.h>
#include <WiFi.h>
#include <Update.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>
WiFiClient esp32_client;
PubSubClient client(esp32_client);

int contentLength = 0;
bool isValidContentType = false;

const char *str = ".bin";
const char *mqtt_broker = "192.168.50.180";
const char *topic = "ota";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *SSID = "apsu";
const char *PSWD = "yangpaopao";

// String host = "sicko.oss-cn-shanghai.aliyuncs.com";
int port = 80;
String bin = "/qq.ino.bin";

String getHeaderValue(String header, String headerName)
{
  return header.substring(strlen(headerName.c_str()));
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message:");
  payload[length] = '\0';
  Serial.println((char *)payload);

  if ((String((char *)payload).indexOf("aliyuncs")) > 0)
  {
    Serial.println("FETCHING SUCCESSFULLY!");
    t_httpUpdate_return ret = ESPhttpUpdate.update((String((char *)payload)));

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
  Serial.println("-----------------------");
}

void setup()
{

  Serial.begin(115200);
  delay(10);
  Serial.println("wifi---Connecting to ");

  WiFi.begin(SSID, PSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi connecting");
    delay(1000);
  }
  Serial.println("wifi --Connected");
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected())
  {
    String client_id = "";
    Serial.println("client is connecting");
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
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
  client.subscribe(topic);
}

void loop()
{
  client.loop();
}
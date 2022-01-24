#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#define APSSID "apsu"
#define APPSK "yangpaopao"

String comment = "";

const char *mqtt_broker = "192.168.50.180";
const char *topic = "top/dev";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

WiFiClient espclient;
PubSubClient client(espclient);
int contentLength = 0;
bool isValidContentType = false;
void update_started()
{
  Serial.println("CALLBACK:  HTTP update process started");
}

void update_finished()
{
  Serial.println("CALLBACK:  HTTP update process finished");
}

void update_progress(int cur, int total)
{
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void update_error(int err)
{
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.println("Message:");

  payload[length] = '\0';
  Serial.println((char *)payload);
 if ((String((char *)payload).indexOf("aliyuncs")) > 0)
  {
    Serial.println("NEED UPDATE!!!");
       ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
       ESPhttpUpdate.onStart(update_started);
       ESPhttpUpdate.onEnd(update_finished);
       ESPhttpUpdate.onProgress(update_progress);
       ESPhttpUpdate.onError(update_error);
    
       t_httpUpdate_return ret = ESPhttpUpdate.update(espclient, (String((char *)payload)));
    
    
       switch (ret) {
         case HTTP_UPDATE_FAILED:
           Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
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
  Serial.println();
  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  WiFi.begin(APSSID, APPSK);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected())
  {
    String client_id = "";
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("Public emqx mqtt broker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  if (Serial.available())
  {
    comment = Serial.readStringUntil('\n');
    comment.trim();
  }
  // publish and subscribe
  client.publish(topic, comment.c_str());
  client.subscribe(topic);
}



void loop()
{
  client.loop();
}
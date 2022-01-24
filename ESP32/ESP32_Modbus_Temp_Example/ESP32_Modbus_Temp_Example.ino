/*
 * !NEED to install EspSoftwareSerial.h before USING!
 */

#include <SoftwareSerial.h>
#include <ModbusMaster.h>
#include <Mqtt.h>

const char *mqtt_broker = "192.168.50.180";
const char *topic = "ota";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *SSID = "apsu";
const char *PSWD = "yangpaopao";

SoftwareSerial mySerial(16, 17); // RX, TX

ModbusMaster node;

void setup()
{
  Serial.begin(4800);
  mySerial.begin(4800);
  node.begin(1, mySerial);
  WiFi.begin(SSID, PSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  // callback参数为可选
  //   Mqtt_connect(mqtt_broker, mqtt_port, mqtt_username, mqtt_password)
  Mqtt_connect(mqtt_broker, mqtt_port, mqtt_username, mqtt_password);
  Mqtt_sub(topic);
}

float data[9];
void loop()
{

  uint16_t result;
  // args1:Temp Read register address : 1
  // args2: 1 16-bit
  result = node.readHoldingRegisters(1, 1);

  data[0] = node.getResponseBuffer(0);
  Serial.println(data[0] / 10);
  float temp = data[0] / 10;
  char buffer[7];
  // float to char[]
  dtostrf(temp, 4, 6, buffer);
  delay(1000);
  Mqtt_pub(topic, buffer);
  Mqtt_loop();
}

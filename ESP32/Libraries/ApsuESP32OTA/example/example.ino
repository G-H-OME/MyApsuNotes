#include <Arduino.h>
#include "Esp32httpOta.h"
#include "Wifi.h"
void setup()
{
  Serial.begin(115200);
  Wifi_connect("apsu", "yangpaopao");
  Ota_update("http://sicko.oss-cn-shanghai.aliyuncs.com/6.0.ino.nodemcu-32s.bin");
}

void loop()
{
}
#include <Arduino.h>
#include "Wifi.h"
void setup()
{
  Serial.begin(115200);
  Wifi_connect("apsu", "yangpaopao");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
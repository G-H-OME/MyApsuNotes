#include <WiFi.h>

char ssid[] = "apsu";           // Enter your WiFi name
char password[] = "yangpaopao"; // Enter WiFi password

WiFiClient espClient;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop()
{
  // todo
}
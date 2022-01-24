
#include <SoftwareSerial.h>

SoftwareSerial mySerial(16, 17); // RX, TX
unsigned char senddata[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

void setup()
{

  Serial.begin(4800);
  while (!Serial)
  {
    ;
  }

  mySerial.begin(4800);
}

void loop()
{ // run over and over
  int i = 0;
  delay(1000);
  for (i = 0; i < 8; i++)
    mySerial.write(senddata[i]);

  delay(100);
  String data[9];
  int j = 0;
  while (mySerial.available())
  {
    unsigned char in = (unsigned char)mySerial.read();

    data[j] = in;
    j++;
  }

  if (data)
  {
    Serial.print("Temp:");
    Serial.println((data[5].toInt() * 256 + data[6].toInt()) / 10.00);
  }
}

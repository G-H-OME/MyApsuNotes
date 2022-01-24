#include <ESP8266WiFi.h>

const char* ssid="apsu";
const char* password="yangpaopao";

// 在esp8266中D7 pin口就是 arduino中的13 pin 口
int outD7 = 13;
WiFiServer server(80);

void setup(){
  Serial.begin(115200);
  delay(10);

  pinMode(outD7,OUTPUT);
  digitalWrite(outD7,0);

  Serial.println();
  Serial.println();
  Serial.print("Connect to");
  Serial.println(ssid);

  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi is connected!");
  
  server.begin();
  Serial.println("Server is started! ");

  Serial.println(WiFi.localIP());
}

void loop(){
  WiFiClient client = server.available();

  if(!client){
    return;
  }

  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  int val = 0;
  if(req.indexOf('/gpio/0') != -1){digitalWrite(outD7,0);val=0;return;}
    
  else if(req.indexOf('/gpio/1') != -1){digitalWrite(outD7,1); val=1;return;}
   
  else{
    Serial.println("invialid request!");
    client.stop();
    return;  
  }
  delay(10);
  client.flush();

  String S = (val)?"high":"low";
  
  client.println(S);
  delay(1);
  Serial.println("client disconneted!");
}

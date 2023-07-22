#include<ESP8266WiFi.h>
const char* ssid="jitesh";
const char* pass="password";
WiFiServer server(80);   

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,pass);
  Serial.println("connecting to");
  Serial.println(ssid);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(50);
    }
 Serial.println();
  Serial.println("connected successfully");
 
  server.begin();
  Serial.println("server is begin at IP address");
  Serial.println(WiFi.localIP());
}
void loop()
{

 WiFiClient clientobj = server.available();
 if (!clientobj) {

    return;
 }
      Serial.println("New Client");
    
 
      while(!clientobj.available()) {
        
      }
    String req = clientobj.readString();
      Serial.println(req);
      String resp = "HTTP/1.1 200 OK\r\n Content-type:text/html\r\n\r\n<!DOCTYPE HTML><HTML><BODY>Hi from ESP </BODY></HTML>";
      clientobj.print(resp);// sending response back to the client
   
    clientobj.stop();
  }


  

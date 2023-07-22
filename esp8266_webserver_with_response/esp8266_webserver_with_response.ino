#include <ESP8266WiFi.h>

const char* ssid = "sontywifi";
const char* pass = "Tanushree@123";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected successfully");

  server.begin();
  Serial.println("Server is listening on IP address:");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient clientobj = server.available();
  if (!clientobj) {
    return;
  }
  Serial.println("New Client");
  while (!clientobj.available()) {
  }
  String req = clientobj.readString();
  Serial.println(req);
  String resp = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n<!DOCTYPE HTML><HTML><BODY>Hi from ESP </BODY></HTML>";
  clientobj.print(resp); // sending response back to the client
  clientobj.stop();
}
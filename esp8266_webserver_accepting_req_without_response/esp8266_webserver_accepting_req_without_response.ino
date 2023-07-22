#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "sontywifi"
#define STAPSK "Tanusree@123"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server is listening on IP address:");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient clientobj = server.available();

  if (clientobj) {
    Serial.println("New Client");

    String req = clientobj.readString();
    req += "HTTP/1.1 200 OK\r\n";
    req += "Content-Type: text/html\r\n";
    req += "Connection: close\r\n\r\n";
    req += "<!DOCTYPE html><html><head><title>ESP8266 Web Server</title></head><body>";
    req += "<h1>Welcome to ESP8266 Web Server</h1>";
    req += "<p>This is a test page.</p>";
    req += "</body></html>";

    Serial.println(req);
    clientobj.print(req);
    clientobj.stop();
  }
}

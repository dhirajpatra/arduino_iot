#include <ESP8266WiFi.h> // header file for nodemcu
#include "DHT.h"         // header file for DHT sensor

const char* ssid = "your wifi username"; //write your ssid
const char* password = "your wifi password";//write your password

const char* host = "api.thingspeak.com"; // this is the server name

const char* THINGSPEAK_API_KEY = "your write api_key "; // //  Enter your Write API key from ThingSpeak

#define DHTPIN 12         //pin where the dht11 is connected GPIO12
 DHT dht(DHTPIN, DHT11); // creating object of DHT type

void setup() {
  Serial.begin(115200);   // begin serial Monitor at 115200 baud rate
  delay(10);
   dht.begin(); // begin dht sensor library
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   // printing IP address of NodeMCU at serial Monitor
}

void loop() {      
    Serial.print("connecting to ");
    Serial.println(host);
    
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    
    const int httpPort = 80;
    
    if (!client.connect(host, httpPort)) // client.connect(URL, port) 
    {
      Serial.println("connection failed");
      return;
    }

    // read values from the sensor
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    
 if (isnan(humidity) || isnan(temperature))   //checking humidity and temperature is a number or not 
   {
    Serial.println("Failed to read from DHT sensor!");
     return;
   }
    //url=update?api_key= THINGSPEAK_API_KEY&field1=String(temperature)&field2=String(humidity)
    
    // We now create a URI for the request
    String url= "/update?api_key=";
    url += THINGSPEAK_API_KEY; // appending 
    url += "&field1=";
    url += String(temperature);// converting temperature into string
    url += "&field2=";
    url += String(humidity);// converting humidity into string
    
    Serial.print("Requesting URL: ");
    Serial.println(url);
    
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
    delay(10);
    while(!client.available()){
      delay(100);
      Serial.print(".");
    }
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    Serial.println("closing connection");
// Go back to sleep. If your sensor is battery powered you might
// want to use deep sleep here
  delay(4000 );
}

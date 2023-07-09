/* 
 * ESP8266 NodeMCU DHT11 - Humidity Temperature Sensor Example
 * 
 * 
 */
 
#include "DHTesp.h"

#define DHTpin 12    // GPIO12

DHTesp dht;

void setup()
{
  Serial.begin(115200);
  
  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);

  // use this instead: 
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 12
  //dht.setup(DHTpin, DHTesp::DHT22); //for DHT22 Connect DHT sensor to GPIO 12
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
}
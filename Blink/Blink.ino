/**
power/output pin from led to ESP pin 12
another pin to gnd from led
*/

const int ledPin = 12;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, LOW);   // Turn on the LED
  delay(1000);                  // Wait for 1 second
  digitalWrite(ledPin, HIGH);    // Turn off the LED
  delay(2000);                  // Wait for 1 second
}

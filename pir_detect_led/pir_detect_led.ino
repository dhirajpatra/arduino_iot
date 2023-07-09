const int inPin = 2;   // Change to the appropriate digital pin connected to the PIR sensor
const int outPin = 12;

void setup() {
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int pirState = digitalRead(inPin);

  // Check if any reading failed
  if (pirState == LOW || pirState == HIGH) {
    Serial.println("PIR state:");
    Serial.println(pirState);

    if (pirState == HIGH) {
      Serial.println("Motion detected!");
      digitalWrite(outPin, HIGH);
      delay(1000);
      digitalWrite(outPin, LOW);
    } else {
      digitalWrite(outPin, LOW);
      Serial.println("Motion not detected!");
    }
  } else {
    Serial.println("Failed to read sensor data!");
  }

  delay(500);  // Adjust delay as needed
}

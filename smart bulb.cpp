int pirPin = 2;        // PIR sensor output pin
int relayPin = 8;      // Relay control pin
int pirState = LOW;    // PIR state
unsigned long motionDetectedTime = 0;
bool motionFlag = false;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Turn off bulb initially
  Serial.begin(9600);
}

void loop() {
  int motion = digitalRead(pirPin);

  if (!motionFlag && motion == HIGH) {
    // Motion detected, start 3s timer
    motionDetectedTime = millis();
    motionFlag = true;
    Serial.println("Motion detected! Waiting 3s to confirm...");
  }

  if (motionFlag) {
    if (millis() - motionDetectedTime >= 3000) { // 3 seconds passed
      int motionCheck = digitalRead(pirPin);
      if (motionCheck == HIGH) {
        digitalWrite(relayPin, HIGH); // Turn on bulb
        Serial.println("Person confirmed, bulb ON.");
        pirState = HIGH;
      } else {
        digitalWrite(relayPin, LOW); // Turn off bulb
        Serial.println("No person after 3s, bulb OFF.");
        pirState = LOW;
      }
      motionFlag = false; // Reset for next detection
    }
  }

  // If bulb is ON, turn it OFF when no motion
  if (pirState == HIGH && digitalRead(pirPin) == LOW) {
    digitalWrite(relayPin, LOW);
    Serial.println("Person left, bulb OFF.");
    pirState = LOW;
  }
}

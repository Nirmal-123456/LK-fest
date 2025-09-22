const int buttonPin = 2; // Bullseye button
const int ledPin = 8;    // LED indicator

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Button pressed = LOW
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // LED off initially
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // Button pressed
    digitalWrite(ledPin, HIGH);        // LED ON
    delay(1000);                       // LED stays ON for 1 second
    digitalWrite(ledPin, LOW);         // LED OFF
    // Optional: wait for button release
    while (digitalRead(buttonPin) == LOW) {
      delay(10);
    }
  }
}
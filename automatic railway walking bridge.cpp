#include <Servo.h>

Servo bridgeServo;

// IR sensor pins
const int ir1 = 2;
const int ir2 = 3;
const int ir3 = 4;

// Output pins
const int buzzer = 6;
const int led = 7;
const int servoPin = 9;

// State variables
bool warningActive = false;
bool bridgeUp = false;

void setup() {
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  bridgeServo.attach(servoPin);
  bridgeServo.write(0); // Bridge down initially
}

void loop() {
  int s1 = digitalRead(ir1);
  int s2 = digitalRead(ir2);
  int s3 = digitalRead(ir3);

  // IR sensors give LOW when object is detected

  // Train approaching
  if (s1 == LOW && !warningActive) { 
    digitalWrite(led, HIGH);     // Warning ON
    digitalWrite(buzzer, HIGH);
    warningActive = true;
  }

  // Train at bridge, lift bridge
  if (s2 == LOW && !bridgeUp) {
    bridgeServo.write(90);       // Lift bridge
    bridgeUp = true;
  }

  // Train passed, reset everything
  if (s3 == LOW) {
    digitalWrite(led, LOW);      // Warning OFF
    digitalWrite(buzzer, LOW);
    bridgeServo.write(0);        // Lower bridge
    warningActive = false;
    bridgeUp = false;
    delay(500); // Debounce to avoid repeated triggers
  }

  delay(100);
}
#include <Servo.h>
#define trigPin 8
#define echoPin 7
#define servoPin 9

#define DISTANCE_THRESHOLD 20 // Distance threshold in cm

// L298N Motor Driver Pins
#define IN1 2 // Left motor forward
#define IN2 3 // Left motor backward
#define IN3 4 // Right motor forward
#define IN4 5 // Right motor backward

Servo shooter;

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  shooter.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm

  if (distance < DISTANCE_THRESHOLD) {
    stopTank();
    fire();
    delay(1000); // wait before next shot
  } else {
    moveForward();
  }
}

// Rotate servo to 90 degrees to trigger the firing mechanism
void fire() {
  shooter.write(90); // adjust angle to release ball
  delay(500);
  shooter.write(0); // reset to initial position (0 degrees)
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopTank() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

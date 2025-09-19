// Simple Obstacle Avoiding Robot
// Hardware: Arduino Uno, L298N (or L293D) motor driver, HC-SR04 ultrasonic sensor

// Motor control pins
const int R_IN1 = 8;   // Right motor forward
const int R_IN2 = 9;   // Right motor backward
const int L_IN1 = 10;  // Left motor forward
const int L_IN2 = 11;  // Left motor backward

// If you connected ENA/ENB to PWM pins, set them here (optional)
const int ENA = 5; // PWM for right motor speed (optional)
const int ENB = 6; // PWM for left motor speed (optional)
const int MOTOR_SPEED = 200; // 0-255 PWM (adjust to taste)

// Ultrasonic pins
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;

long duration_us;
float distance_cm;
const float DIST_THRESHOLD = 20.0; // cm - obstacle threshold

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(R_IN1, OUTPUT);
  pinMode(R_IN2, OUTPUT);
  pinMode(L_IN1, OUTPUT);
  pinMode(L_IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Start stopped
  stopMotors();
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void loop() {
  distance_cm = readUltrasonicCM();
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if (distance_cm > 0 && distance_cm <= DIST_THRESHOLD) {
    // Obstacle detected: back up and turn
    Serial.println("Obstacle! backing up...");
    backUp(300);   // ms
    turnRight(350); // ms (adjust to change turn angle)
  } else {
    // No obstacle: move forward
    forward();
  }

  delay(50);
}

/* Motor helper functions */
void forward() {
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void backUp(int ms) {
  digitalWrite(R_IN1, LOW);
  digitalWrite(R_IN2, HIGH);
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  delay(ms);
  stopMotors();
}

void turnRight(int ms) {
  // Right wheel backward, left wheel forward (spin right)
  digitalWrite(R_IN1, LOW);
  digitalWrite(R_IN2, HIGH);
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  delay(ms);
  stopMotors();
}

void turnLeft(int ms) {
  // Right wheel forward, left wheel backward (spin left)
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  delay(ms);
  stopMotors();
}

void stopMotors() {
  digitalWrite(R_IN1, LOW);
  digitalWrite(R_IN2, LOW);
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

/* Ultrasonic distance read (returns cm) */
float readUltrasonicCM() {
  // Clear trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send 10us pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pulse
  duration_us = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30 ms
  if (duration_us == 0) return -1.0; // no echo (out of range or error)

  // Speed of sound ~343 m/s => distance cm = duration_us / 58.0
  float cm = duration_us / 58.0;
  return cm;
}

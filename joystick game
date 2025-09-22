#include <Servo.h>

Servo servo1;
Servo servo2;
const int joyX = 0; // Analog pin for X-axis
const int joyY = 1; // Analog pin for Y-axis

unsigned long previousMillis = 0; // Timer variable for Serial output
const unsigned long interval = 500; // Interval for Serial output in milliseconds

void setup()
{
  Serial.begin(9600); // Initialize serial communication at 9600 bps
  servo1.attach(3);   // Connect servo1 to digital pin 3
  servo2.attach(5);   // Connect servo2 to digital pin 5
}

void loop()
{
  int joyXVal = analogRead(joyX);
  int joyYVal = analogRead(joyY);

  int servo1Pos = map(joyXVal, 0, 1023, 180, 130);
  int servo2Pos = map(joyYVal, 0, 1023, 130, 180);

  servo1.write(servo1Pos);
  servo2.write(servo2Pos);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    Serial.print("Joystick X: ");
    Serial.print(joyXVal);
    Serial.print(" -> Servo1 Position: ");
    Serial.println(servo1Pos);

    Serial.print("Joystick Y: ");
    Serial.print(joyYVal);
    Serial.print(" -> Servo2 Position: ");
    Serial.println(servo2Pos);
  }

  delay(50); // Small delay for stable servo movement
}


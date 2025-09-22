#include <Wire.h>
#include <SPI.h>
#include <RF24.h>
#include <MPU6050.h>

#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "NODE1";

MPU6050 mpu;
float pitch = 0;
unsigned long lastMicros = 0;

// Optional: Add a button for command sending
const int buttonPin = 2; // Connect a button to pin 2

struct TxPayload {
  int16_t pitch_deg;
  int8_t cmd;
};

void setup() {
  Wire.begin();
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP); // Button pressed = LOW
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
  }
  radio.begin();
  radio.setRetries(3,5);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();
  lastMicros = micros();
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  unsigned long now = micros();
  float dt = (now - lastMicros) / 1000000.0;
  lastMicros = now;

  float accelPitch = atan2((float)ax, sqrt((float)ay*ay + (float)az*az)) * 180.0 / PI;
  float gyroY = (float)gy / 131.0;

  const float alpha = 0.98;
  pitch = alpha * (pitch + gyroY * dt) + (1 - alpha) * accelPitch;

  TxPayload data;
  data.pitch_deg = (int16_t)round(pitch * 100.0);

  // Button command: 1 if pressed, 0 otherwise
  data.cmd = (digitalRead(buttonPin) == LOW) ? 1 : 0;

  radio.write(&data, sizeof(data));
  Serial.print("Pitch: "); Serial.print(pitch);
  Serial.print(" | Cmd: "); Serial.println(data.cmd);
  delay(30);
}
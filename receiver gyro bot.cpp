#include <SPI.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "NODE1";

struct RxPayload {
  int16_t pitch_deg;
  int8_t cmd;
};

const int IN1 = 4;
const int IN2 = 5;
const int ENA = 2;
const int IN3 = 6;
const int IN4 = 7;
const int ENB = 3;

float Kp = 0.8;
float Ki = 0.0;
float Kd = 0.0;

float integral = 0;
float lastError = 0;
unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  lastTime = millis();
}

void loop() {
  if (radio.available()) {
    RxPayload data;
    radio.read(&data, sizeof(data));
    float pitch = data.pitch_deg / 100.0;

    float error = -pitch;
    unsigned long now = millis();
    float dt = (now - lastTime) / 1000.0;
    lastTime = now;

    integral += error * dt;
    float derivative = (error - lastError) / (dt > 0 ? dt : 1);
    lastError = error;

    float output = Kp * error + Ki * integral + Kd * derivative;
    int pwm = constrain((int)round(output * 10.0), -255, 255);

    // If button command received, stop motors
    if (data.cmd == 1) {
      setMotorPWM(0);
      Serial.println("Button pressed: Motors stopped.");
    } else {
      setMotorPWM(pwm);
      Serial.print("Pitch:"); Serial.print(pitch);
      Serial.print(" pwm:"); Serial.println(pwm);
    }
  }
}

void setMotorPWM(int pwm) {
  if (pwm > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, pwm);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, pwm);
  } else if (pwm < 0) {
    pwm = -pwm;
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, pwm);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, pwm);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
  }
}
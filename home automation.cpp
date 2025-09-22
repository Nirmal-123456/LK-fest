#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_DEVICE_NAME "YourDeviceName"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h> // Use <BlynkSimpleEsp8266.h> for ESP8266

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

int relayPin = 8; // Relay control pin

void setup()
{
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Bulb OFF initially
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

// Blynk button widget on V0
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  digitalWrite(relayPin, value); // 1 = ON, 0 = OFF
}

void loop()
{
  Blynk.run();
}
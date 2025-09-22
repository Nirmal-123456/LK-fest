int soundsensor = 3;
int leds[] = {7, 8, 9, 10}; // Array of LED pin numbers
const int numLeds = sizeof(leds) / sizeof(leds[0]);

void setup() 
{ 
  pinMode(soundsensor, INPUT);
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  int sensorvalue = digitalRead(soundsensor);
  if (sensorvalue == 1)
  {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }
  else
  {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], LOW);
    }
  }
}

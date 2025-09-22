void waitForStart() {
  // Wait until START pin pressed (grounded) or any button pressed
  while (digitalRead(START_PIN) == HIGH) {
    for (uint8_t b = 0; b < 4; b++) {
      if (buttonPressed(b)) {
        // Blink the corresponding LED while the button is held
        while (buttonPressed(b)) {
          digitalWrite(LED_PINS[b], HIGH);
          delay(100);
          digitalWrite(LED_PINS[b], LOW);
          delay(100);
        }
        // Button released, start the game
        delay(150); // debounce
        return;
      }
    }
    delay(50);
  }
  // START pin pressed, start the game
  delay(150); // debounce
}

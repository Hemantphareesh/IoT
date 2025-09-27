#define LED_PIN 6   // LED2 connected to D6
#define SW_PIN 2    // SW2 connected to D2

#define DEBOUNCE_DELAY 50 // ms

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PIN, INPUT_PULLUP); // switch with internal pull-up
}

void loop() {
  // Read switch (LOW when pressed)
  int sw_state = digitalRead(SW_PIN);

  if (sw_state == LOW) {
    delay(DEBOUNCE_DELAY);            // debounce delay
    if (digitalRead(SW_PIN) == LOW) { // still pressed
      digitalWrite(LED_PIN, HIGH);    // LED ON
    }
  } else {
    digitalWrite(LED_PIN, LOW);       // LED OFF
  }
}

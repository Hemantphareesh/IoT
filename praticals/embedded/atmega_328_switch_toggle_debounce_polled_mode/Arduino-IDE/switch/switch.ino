#define LED_PIN 6   // LED2 connected to D6
#define SW_PIN 2    // SW2 connected to D2 (INT0)

volatile bool toggle_request = false;
volatile bool led_state = false;

// ISR: runs automatically when switch pressed (falling edge)
void switchISR() {
  toggle_request = true;  
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PIN, INPUT_PULLUP); // internal pull-up

  // Attach interrupt on falling edge
  attachInterrupt(digitalPinToInterrupt(SW_PIN), switchISR, FALLING);
}

void loop() {
  if (toggle_request) {
    delay(50); // debounce
    if (digitalRead(SW_PIN) == LOW) { // still pressed
      led_state = !led_state;         // toggle LED state
      digitalWrite(LED_PIN, led_state);
    }
    toggle_request = false; // clear flag
  }
}

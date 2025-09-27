#define LED_PIN 6     // LED connected to D6
#define SW_PIN 2      // Switch connected to D2

void setup() {
  pinMode(LED_PIN, OUTPUT);       // set D6 as output
  pinMode(SW_PIN, INPUT_PULLUP);  // set D2 as input with pull-up
}

void loop() {
  if (digitalRead(SW_PIN) == LOW) {  
    // switch pressed (active LOW)
    digitalWrite(LED_PIN, HIGH);  // LED ON
  } else {
    // switch released
    digitalWrite(LED_PIN, LOW);   // LED OFF
  }
}

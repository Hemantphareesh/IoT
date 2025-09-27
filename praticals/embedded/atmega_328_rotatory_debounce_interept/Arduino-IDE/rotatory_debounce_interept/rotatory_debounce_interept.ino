#define LED_PIN 6       // Arduino digital pin D6
#define ENC_A_PIN 2     // Rotary encoder A → Arduino D2 (INT0)
#define ENC_B_PIN 3     // Rotary encoder B → Arduino D3 (INT1)

volatile int8_t encoder_dir = 0;     // +1 for CW, -1 for CCW
volatile uint16_t cw_count = 0;      // CW step counter
volatile uint16_t ccw_count = 0;     // CCW step counter

// Debounce delay in microseconds
#define DEBOUNCE_DELAY_US 2000  

// Store last stable states
volatile uint8_t last_A = 0;
volatile uint8_t last_B = 0;

void handleA() {
  delayMicroseconds(DEBOUNCE_DELAY_US); // debounce
  uint8_t A = digitalRead(ENC_A_PIN);
  uint8_t B = digitalRead(ENC_B_PIN);

  if (A != last_A) {   // A changed
    if (A == B) {
      encoder_dir = -1; // CCW
      ccw_count++;
    } else {
      encoder_dir = +1; // CW
      cw_count++;
    }
    last_A = A;
  }
}

void handleB() {
  delayMicroseconds(DEBOUNCE_DELAY_US); // debounce
  uint8_t A = digitalRead(ENC_A_PIN);
  uint8_t B = digitalRead(ENC_B_PIN);

  if (B != last_B) {   // B changed
    if (A == B) {
      encoder_dir = +1; // CW
      cw_count++;
    } else {
      encoder_dir = -1; // CCW
      ccw_count++;
    }
    last_B = B;
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // LED OFF initially

  pinMode(ENC_A_PIN, INPUT_PULLUP);
  pinMode(ENC_B_PIN, INPUT_PULLUP);

  last_A = digitalRead(ENC_A_PIN);
  last_B = digitalRead(ENC_B_PIN);

  // Attach interrupts on encoder pins
  attachInterrupt(digitalPinToInterrupt(ENC_A_PIN), handleA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B_PIN), handleB, CHANGE);
}

void loop() {
  // Check conditions
  if (cw_count >= 3) {
    digitalWrite(LED_PIN, HIGH);  // LED ON
    cw_count = 0;
  }
  if (ccw_count >= 6) {
    digitalWrite(LED_PIN, LOW);   // LED OFF
    ccw_count = 0;
  }
}

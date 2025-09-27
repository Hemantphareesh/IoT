// Toggle LED every 4 seconds using Timer1 

const int LED_PIN = 6;   // LED connected to digital pin 6
volatile bool toggleFlag = false;  

ISR(TIMER1_COMPA_vect) {
  toggleFlag = true;  // Set flag when interrupt fires
}

void setup() {
  pinMode(LED_PIN, OUTPUT);

  // --- Timer1 Setup ---
  noInterrupts();           // Disable interrupts during setup
  TCCR1A = 0;               // Clear Timer1 control register A
  TCCR1B = 0;               // Clear Timer1 control register B

  // Compare value for 4 seconds (16MHz / 1024 = 15625 ticks/sec)
  OCR1A = 62500 - 1;        // 4 seconds

  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024

  TIMSK1 |= (1 << OCIE1A);  // Enable compare interrupt
  interrupts();             // Enable global interrupts
}

void loop() {
  if (toggleFlag) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED
    toggleFlag = false;
  }
}

#define LED_PIN 6       // Arduino pin D6
#define ENC_A_PIN 2     // CLK (A) → D2
#define ENC_B_PIN 3     // DT (B) → D3

int step_count = 0;
int last_state = 0;

int read_encoder() {
  return (digitalRead(ENC_A_PIN) ? 1 : 0) |
         (digitalRead(ENC_B_PIN) ? 2 : 0);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(ENC_A_PIN, INPUT_PULLUP);  // Enable internal pull-up
  pinMode(ENC_B_PIN, INPUT_PULLUP);  // Enable internal pull-up

  last_state = read_encoder();
}

void loop() {
  int curr_state = read_encoder();

  if (curr_state != last_state) {
    // Clockwise sequence
    if ((last_state == 0 && curr_state == 1) ||
        (last_state == 1 && curr_state == 3) ||
        (last_state == 3 && curr_state == 2) ||
        (last_state == 2 && curr_state == 0)) {
      step_count++; // Clockwise
    } 
    // Counter-clockwise sequence
    else if ((last_state == 0 && curr_state == 2) ||
             (last_state == 2 && curr_state == 3) ||
             (last_state == 3 && curr_state == 1) ||
             (last_state == 1 && curr_state == 0)) {
      step_count--; // Counter-clockwise
    }

    // LED control
    if (step_count >= 1) {          // 1 CW step → ON
      digitalWrite(LED_PIN, HIGH);
      step_count = 0;
    } else if (step_count <= -1) {  // 1 CCW step → OFF
      digitalWrite(LED_PIN, LOW);
      step_count = 0;
    }

    last_state = curr_state;
  }

  delay(2); // debounce
}

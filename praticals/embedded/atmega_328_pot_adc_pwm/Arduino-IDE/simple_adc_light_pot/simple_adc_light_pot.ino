int ledPin = 6;  // PD6 = Digital Pin 6 on Arduino Uno

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin as output
}

void loop() {
  // Fade in
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);  // Set PWM duty cycle
    delay(10);                        // Adjust fading speed
  }

  // Fade out
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(10);
  }
}

// === Pin Definitions ===
const int potPin = A0;    // Potentiometer input (ADC0)
const int ledPin = 6;     // PWM output pin (OC0A = PD6)

void setup() {
  pinMode(ledPin, OUTPUT);   // Set PD6 as output
}

void loop() {
  int adc_val = analogRead(potPin);   // Read 10-bit ADC value (0–1023)
  int pwm_value = adc_val / 4;        // Scale to 8-bit (0–255)
  analogWrite(ledPin, pwm_value);     // Set PWM duty cycle
  delay(5);                           // Small delay for smoother response
}

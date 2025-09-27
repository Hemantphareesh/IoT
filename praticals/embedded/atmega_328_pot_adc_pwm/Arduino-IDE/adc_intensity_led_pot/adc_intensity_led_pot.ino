const int ledPin = 6;   // PD6 → Arduino digital pin 6
const int adcPin = A0;  // ADC0 → Arduino analog pin A0

void setup() {
  pinMode(ledPin, OUTPUT);   // LED pin as output
}

void loop() {
  int adc_value = analogRead(adcPin);  // 10-bit ADC value (0–1023)

  // Check if ADC value is above 50% threshold (~512)
  if (adc_value > 512) {
    digitalWrite(ledPin, HIGH);  // Turn LED ON
  } else {
    digitalWrite(ledPin, LOW);   // Turn LED OFF
  }

  delay(50);  // Small delay for stability
}

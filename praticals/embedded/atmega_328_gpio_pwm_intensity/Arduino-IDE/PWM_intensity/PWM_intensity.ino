int ledPin = 6; // On Arduino Uno, pin 6 has the built-in LED

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin as output
}

void loop() {
  digitalWrite(ledPin, HIGH); // Turn LED ON
  delay(5000);                // Wait 5 seconds

  digitalWrite(ledPin, LOW);  // Turn LED OFF
  delay(5000);                // Wait 5 seconds
}

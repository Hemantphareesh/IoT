#include <Wire.h>  // I2C library

#define EEPROM_ADDR 0x50  // 24C32 default I2C address

void setup() {
  // Initialize UART
  Serial.begin(115200);
  while (!Serial); // Wait for Serial connection (optional)

  Serial.println("EEPROM Arduino (0x50)");
  Serial.println("Writing 0..10");

  Wire.begin(); // Initialize I2C

  // Write 0..10 to EEPROM
  for (uint8_t i = 0; i <= 10; i++) {
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((uint8_t)(i >> 8));    // high byte of memory address
    Wire.write((uint8_t)(i & 0xFF));  // low byte
    Wire.write(i);                     // data
    Wire.endTransmission();
    delay(5); // write cycle
  }

  Serial.println("Read back:");

  // Read back and print
  for (uint8_t i = 0; i <= 10; i++) {
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((uint8_t)(i >> 8));    // high byte
    Wire.write((uint8_t)(i & 0xFF));  // low byte
    Wire.endTransmission();

    Wire.requestFrom(EEPROM_ADDR, (uint8_t)1);
    uint8_t val = 0;
    if (Wire.available()) val = Wire.read();

    Serial.print("Addr ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(val);
  }
}

void loop() {
  // Nothing to do
}

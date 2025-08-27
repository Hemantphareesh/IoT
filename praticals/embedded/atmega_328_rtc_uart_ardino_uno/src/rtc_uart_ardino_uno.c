#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);      // Serial at 115200 baud
  Wire.begin();              // Start I2C

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, setting time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
    // sets RTC to the time when sketch was compiled
  }
}

void loop() {
  DateTime now = rtc.now();

  Serial.print("Date: ");
  Serial.print(now.day());
  Serial.print("/");
  Serial.print(now.month());
  Serial.print("/");
  Serial.print(now.year());

  Serial.print("  Time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());

  Serial.println();

  delay(30000);  // wait 30 seconds
}

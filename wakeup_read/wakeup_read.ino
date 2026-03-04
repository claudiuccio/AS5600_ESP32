#include <Wire.h>
#include <AS5600.h>

AS5600 as5600;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA, SCL per ESP32

  Serial.println("Test AS5600...");

  if (!as5600.begin()) {
    Serial.println("AS5600 non trovato! Controlla il cablaggio.");
    while (1);
  }

  Serial.println("AS5600 trovato!");
}

void loop() {
  uint16_t rawAngle = as5600.rawAngle();   // 0 - 4095
  float degrees = as5600.readAngle();      // 0 - 360°

  if (as5600.detectMagnet()) {
    Serial.println("Magnete rilevato!");
  } else {
    Serial.println("Magnete NON rilevato!");
  }

  
  Serial.print("Raw: ");
  Serial.print(rawAngle);
  Serial.print("  |  Gradi: ");
  Serial.println(degrees);

  delay(200);
  
}
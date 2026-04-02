#include <Wire.h>
#include <AS5600.h>
#include <math.h> // Necessaria per fmodf

AS5600 as5600;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); 

  Serial.println("Inizializzazione AS5600...");

  if (!as5600.begin()) {
    Serial.println("Errore: AS5600 non trovato!");
    while (1);
  }
  
  // Opzionale: imposta la direzione se la libreria lo supporta
  // as5600.setDirection(AS5600_CLOCK_WISE); 

  Serial.println("AS5600 pronto.");
}

void loop() {
  // Lettura ultra-diretta del registro dell'angolo (0x0E e 0x0F)
  Wire.beginTransmission(0x36);
  Wire.write(0x0E); 
  Wire.endTransmission();
  Wire.requestFrom(0x36, 2);
  
  if (Wire.available() >= 2) {
    uint16_t high = Wire.read();
    uint16_t low = Wire.read();
    uint16_t realRaw = (high << 8) | low;
    
    float realDeg = (realRaw * 360.0) / 4096.0;

    Serial.print("Vero Raw Hardware: ");
    Serial.print(realRaw);
    Serial.print(" | Vero Grado Hardware: ");
    Serial.println(realDeg);
  }
  delay(100);
}
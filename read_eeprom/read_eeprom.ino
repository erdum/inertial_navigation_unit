#include <EEPROM.h>

unsigned int diskCounter = 0;
float lat;
float lng;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (diskCounter < EEPROM.length()) {
    EEPROM.get(diskCounter, lat);
    diskCounter += sizeof(float);

    EEPROM.get(diskCounter, lng);
    diskCounter += sizeof(float);

    Serial.print(lat, 8);
    Serial.print(", ");
    Serial.println(lng, 8);
  }
}

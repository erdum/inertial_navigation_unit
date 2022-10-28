#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPSPlus.h>

Adafruit_SSD1306 led(128, 64, &Wire, -1);
TinyGPSPlus gps();

unsigned long prevTime = 0;
unsigned int diskCounter = 0;
float lat = 0.0;
float lng = 0.0;
float speed = 0.0;
byte hour = 0;
byte minute = 0;
byte second = 0;
byte numOfSats = 0;
float alttitude = 0;

void storeLocation (float lat, float lng) {
  EEPROM.put(diskCounter, lat);
  diskCounter += sizeof(float);

  EEPROM.put(diskCounter, lng);
  diskCounter += sizeof(float);
}

void displayTime(byte hour, byte minute, byte second) {
  led.print(hour);
  led.print(':');
  led.print(minute);
  led.print(':');
  led.println(second);
}

void setup() {
  Serial.begin(9600);
  led.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  led.clearDisplay();
  led.setTextColor(SSD1306_WHITE);
  led.setTextSize(2);
  led.setCursor(0, 0);
  led.println("AllahuAkbr");
  led.println("Pakistan");
  led.println("Zindabad");
  led.display();
  led.setTextSize(1);
  delay(3000);
}

void loop() {
  led.clearDisplay();
  led.setCursor(0, 0);

  while (Serial.available()) {
    gps.encode(Serial.available());

    if (gps.time.isValid() &&
        gps.location.isValid() &&
        gps.speed.isValid() &&
        gps.satellites.isValid())
    {
      hour = gps.time.hour();
      minute = gps.time.minute();
      second = gps.time.second();

      lat = gps.location.lat();
      lng = gps.location.lng();
      speed = gps.speed.kmph();

      numOfSats = gps.satellites.value();
    }
  }

  if (millis() - prevTime >= 15000 && lat != 0.0 && lng != 0.0) {

    if (diskCounter < EEPROM.length()) storeLocation(lat, lng);
    prevTime = millis();
  }

  led.print("Disk: ");
  led.print((float) diskCounter / 1024.0 * 100.0, 2);
  led.println('%');

  displayTime(hour, minute, second);

  led.print("Lat: ");
  led.println(lat, 6);
  led.print("Lng: ");
  led.println(lng, 6);

  led.print(speed);
  led.println("kmph");

  led.print("Alt: ");
  led.println(alttitude, 2);

  led.print("Number of sats: ");
  led.println(numOfSats);
  led.display();
}

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPSPlus.h>

Adafruit_SSD1306 oled(128, 16, &Wire, -1);
TinyGPSPlus gps;

byte hour = 0;
byte minute = 0;
byte second = 0;
byte speed = 0;
float lat = 0.0;
float lng = 0.0;
unsigned long prevTime = 0;
String fileName;
File disk;

void setup() {
	SD.begin(10);
	Serial.begin(9600);
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3c);
	oled.setTextColor(SSD1306_WHITE);
	oled.setTextSize(1);
	oled.clearDisplay();
	oled.setCursor(0, 0);
  oled.println("Allah u Akbar");
  oled.display();
  delay(2000);
}

void loop() {
	while (Serial.available()) {
    gps.encode(Serial.read());

    if (gps.time.isValid()) {
      hour = gps.time.hour();
      minute = gps.time.minute();
      second = gps.time.second();
    }

    if (gps.location.isValid()) {
	    lat = gps.location.lat();
	    lng = gps.location.lng();
    }

    if (gps.speed.isValid()) {
      speed = gps.speed.kmph();
    }
  }

	if (millis() - prevTime >= 1000 && lat != 0.0 && lng != 0.0) {

		disk = SD.open("gps_data.csv", FILE_WRITE);
		disk.print(lat);
		disk.print(", ");
		disk.println(lng);
		disk.close();

    prevTime = millis();
  }

	oled.clearDisplay();
	oled.setCursor(0, 0);

	if (hour < 10) oled.print('0');
  oled.print(hour);
  oled.print(':');

  if (minute < 10) oled.print('0');
  oled.print(minute);
  oled.print(':');

  if (second < 10) oled.print('0');
  oled.print(second);

  oled.print("  ");
  oled.println(millis() / 1000);

  oled.print(speed);
  oled.println("kmh");

  oled.display();
}

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPSPlus.h>

Adafruit_SSD1306 setupDisplay() {
  Adafruit_SSD1306 display(128, 32, &Wire, -1);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.clearDisplay();
  display.setCursor(0, 0);
  return display;
}

void setup() {
  Adafruit_SSD1306 oled = setupDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
}

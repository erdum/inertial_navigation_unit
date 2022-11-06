#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

Adafruit_SSD1306 led(128, 64, &Wire, -1);

void setupDisplay(Adafruit_SSD1306 led) {
  led.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  led.clearDisplay();
  led.setTextColor(SSD1306_WHITE);
  led.setTextSize(2);
  led.setCursor(0, 0);
  led.println("Allah");
  unsigned int currentTime = millis();
  unsigned int counter = 0;
  while (millis() > currentTime + 3000) {
    led.println(counter);
    led.display();
    counter++;
  }
  led.clearDisplay();
  led.setTextSize(1);
  led.setCursor(0, 0);
}

File mountDisk() {
  sprintf(filename, "%02d%02d%02d.csv", year, month, day);
  SD.begin(10);
  return SD.open("erdum.csv", FILE_WRITE);
}

void setup() {
  setupDisplay(led);
  File disk = mountDisk();
  disk.println("lat, long");
  disk.close();
}

void loop() {
  // put your main code here, to run repeatedly:

}

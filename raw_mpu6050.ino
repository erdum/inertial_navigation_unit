#include <Wire.h>

#define DEV_ADD 0x68
#define DATA_RES (double)(pow(2, 16)/2)
#define DEV_RANGE 2
#define ACC 9.8
long accX;
long tempHold;
double a = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(DEV_ADD);
  Wire.write(0x6b); // pwr_managment_register_1
  Wire.write(0);
  Wire.endTransmission(false);
}

void loop() {
  Wire.beginTransmission(DEV_ADD);
  Wire.write(0x3b);
  Wire.endTransmission(false);

  Wire.requestFrom(DEV_ADD, 2, true);
  accX = Wire.read() << 8 | Wire.read();

  tempHold = accX * DEV_RANGE;
  a = (tempHold / DATA_RES) * ACC;
  Serial.println(a - 0.28);
  delay(50);
}
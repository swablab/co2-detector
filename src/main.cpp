#include <Arduino.h>
#include <MQ135.h>

#define PIN_MQ135 A0
MQ135 mq135_sensor = MQ135(PIN_MQ135);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float val = analogRead(A0);
  Serial.print ("raw = ");
  Serial.println (val);
  float zero = mq135_sensor.getRZero();
  Serial.print ("rzero: ");
  Serial.println (zero);
  float ppm = mq135_sensor.getPPM();
  Serial.print ("ppm: ");
  Serial.println (ppm);
  delay(2000);
}
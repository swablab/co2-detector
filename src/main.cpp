#include <Arduino.h>
#include <MQ135.h>

#define PIN_MQ135 A0
#define PIN_LED_GREEN DD2
#define PIN_LED_YELLOW DD3
#define PIN_LED_RED DD4
#define PIN_NOISE DD5

#define MEASURE_DELAY 1000
#define NOISE_DELAY 100

MQ135 co2_sensor(PIN_MQ135);

void setup() {
  Serial.begin(9600);
  // co2_sensor.setR0(1000.);
}

void printValues(float ppm, float temp, float humidity);

void loop() {
  float value = co2_sensor.getCO2();
  Serial.print("co2: ");
  Serial.println(value);
  delay(2000);
  // if (count >= maxCount || count < 0) {
  //   float temp = bme.readTemperature();
  //   float humidity = bme.readHumidity();
  //   ppm = co2_sensor.getCorrectedPPM(temp, humidity);
    
  //   count = 0;
  //   if (ppm < 1000) {
  //     digitalWrite(PIN_LED_GREEN, 1);
  //     digitalWrite(PIN_LED_YELLOW, 0);
  //     digitalWrite(PIN_LED_RED, 0);
  //   }
  //   else if (ppm <= 2000) {
  //     digitalWrite(PIN_LED_GREEN, 0);
  //     digitalWrite(PIN_LED_YELLOW, 1);
  //     digitalWrite(PIN_LED_RED, 0);
  //   }
  //   else {
  //     digitalWrite(PIN_LED_GREEN, 0);
  //     digitalWrite(PIN_LED_YELLOW, 0);
  //     digitalWrite(PIN_LED_RED, 1);
  //   }

  //   printValues(ppm, temp, humidity);
  // }

  // if (ppm > 2000) {
  //   noise = !noise;
  //   digitalWrite(PIN_NOISE, noise);
  // }
  // else {
  //   digitalWrite(PIN_NOISE, 0);
  // }

  // delay(NOISE_DELAY);
  // count++;
}
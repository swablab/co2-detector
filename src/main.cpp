#include <Arduino.h>
#include <MQ135.h>

#define PIN_MQ135 A0
#define PIN_LED_GREEN DD2
#define PIN_LED_YELLOW DD3
#define PIN_LED_RED DD4
#define PIN_NOISE DD5

#define MEASURE_DELAY 1000
#define NOISE_DELAY 100

const int maxCount = 10;
int count = 0;
bool noise = false;
bool noiseActive = false;

float ppm;

MQ135 co2_sensor(PIN_MQ135);

void setup() {
  Serial.begin(9600);
  co2_sensor.setR0(100);
}

void printValues(float ppm, float temp, float humidity);

void loop() {
  if (count >= maxCount || count < 0) {
    ppm = co2_sensor.getCO2();
    
    count = 0;
    if (ppm < 1000) {
      noiseActive = false;
      digitalWrite(PIN_LED_GREEN, 1);
      digitalWrite(PIN_LED_YELLOW, 0);
      digitalWrite(PIN_LED_RED, 0);
    }
    else if (ppm <= 2000) {
      noiseActive = false;
      digitalWrite(PIN_LED_GREEN, 0);
      digitalWrite(PIN_LED_YELLOW, 1);
      digitalWrite(PIN_LED_RED, 0);
    }
    else {
      noiseActive = true;
      digitalWrite(PIN_LED_GREEN, 0);
      digitalWrite(PIN_LED_YELLOW, 0);
      digitalWrite(PIN_LED_RED, 1);
    }
  }

  if (noiseActive) {
    noise = !noise;
    digitalWrite(PIN_NOISE, noise);
  }
  else {
    digitalWrite(PIN_NOISE, 0);
  }

  delay(NOISE_DELAY);
  count++;
}
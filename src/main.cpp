#include <Arduino.h>
#include <MQ135.h>
#include <Adafruit_BME280.h>

#define PIN_MQ135 A7
#define PIN_NOISE 2
#define PIN_LED_GREEN 3
#define PIN_LED_GREEN2 4
#define PIN_LED_YELLOW 5
#define PIN_LED_YELLOW2 6
#define PIN_LED_RED 7
#define PIN_LED_RED2 8

void printValues();

const int maxCount = 10;
int count = 0;
bool noise = false;
bool noiseActive = false;

float ppm;

MQ135 co2_sensor(PIN_MQ135);
Adafruit_BME280 bme;

void setup() {
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_GREEN2, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_YELLOW2, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_RED2, OUTPUT);
  pinMode(PIN_NOISE, OUTPUT);
  Serial.begin(9600);
  co2_sensor.setR0(300);

  if (!bme.begin(0x76)) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
  }
}

void loop() {
  if (count >= maxCount || count < 0) {
    float temp = bme.readTemperature();
    float humidity = bme.readHumidity();
    ppm = co2_sensor.getCorrectedCO2(temp, humidity);
    
    count = 0;
    noiseActive = false;
    digitalWrite(PIN_LED_GREEN, 0);
    digitalWrite(PIN_LED_GREEN2, 0);
    digitalWrite(PIN_LED_YELLOW, 0);
    digitalWrite(PIN_LED_YELLOW2, 0);
    digitalWrite(PIN_LED_RED, 0);
    digitalWrite(PIN_LED_RED2, 0);

    if (ppm < 1000) {
      digitalWrite(PIN_LED_GREEN, 1);
      if (ppm > 750) {
        digitalWrite(PIN_LED_GREEN2, 1);
      }
    }
    if (ppm > 1000 && ppm <= 2000) {
      digitalWrite(PIN_LED_YELLOW, 1);
      if (ppm > 1500) {
        digitalWrite(PIN_LED_YELLOW2, 1);
      }
    }
    if (ppm > 2000) {
      digitalWrite(PIN_LED_RED, 1);
      if (ppm > 2500) {
        noiseActive = true;
        digitalWrite(PIN_LED_RED2, 1);
      }
    }

    printValues();
  }

  if (noiseActive) {
    noise = !noise;
    // digitalWrite(PIN_NOISE, noise);
  }
  else {
    // digitalWrite(PIN_NOISE, 0);
  }

  delay(100);
  count++;
}

void printValues() {
  float temp = bme.readTemperature();
  float humidity = bme.readHumidity();
  float ppm = co2_sensor.getCO2();
  float cppm = co2_sensor.getCorrectedCO2(temp, humidity);
  Serial.print("ppm: ");
  Serial.println(ppm);
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("corrected ppm: ");
  Serial.println(cppm);
}
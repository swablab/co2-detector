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

float ppm;
bool noiseActive;

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

  // if (!bme.begin(0x76)) {
  //   Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
  // }
}

void loop() {
  // float temp = bme.readTemperature();
  // float humidity = bme.readHumidity();
  ppm = co2_sensor.getCO2();
  
  digitalWrite(PIN_LED_GREEN, 1);
  digitalWrite(PIN_LED_GREEN2, 1);
  digitalWrite(PIN_LED_YELLOW, 1);
  digitalWrite(PIN_LED_YELLOW2, 1);
  digitalWrite(PIN_LED_RED, 1);
  digitalWrite(PIN_LED_RED2, 1);

  printValues();

  if (noiseActive) {
    digitalWrite(PIN_NOISE, 1);
  }
  else {
    digitalWrite(PIN_NOISE, 0);
  }

  delay(100);
  // noiseActive = !noiseActive;
}

void printValues() {
  // float temp = bme.readTemperature();
  // float humidity = bme.readHumidity();
  float ppm = co2_sensor.getCO2();
  // float cppm = co2_sensor.getCorrectedCO2(temp, humidity);
  Serial.print("ppm: ");
  Serial.println(ppm);
  // Serial.print("Temperature: ");
  // Serial.println(temp);
  // Serial.print("Humidity: ");
  // Serial.println(humidity);
  // Serial.print("corrected ppm: ");
  // Serial.println(cppm);
}
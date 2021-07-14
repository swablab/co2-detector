#include <Arduino.h>
#include <MQ135.h>
#include <Adafruit_BME280.h>

#define PIN_MQ135 A0
#define PIN_NOISE 2
#define PIN_LED_GREEN 3
#define PIN_LED_GREEN2 4
#define PIN_LED_YELLOW 5
#define PIN_LED_YELLOW2 6
#define PIN_LED_RED 7
#define PIN_LED_RED2 8

MQ135 co2_sensor(PIN_MQ135);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);

  // if (!bme.begin(0x76)) {
  //   Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
  // }
}

void loop() {
  // float temp = bme.readTemperature();
  // float humidity = bme.readHumidity();

  // float r0 = co2_sensor.getCorrectedR0(temp, humidity);
  float in = analogRead(PIN_MQ135);
  double v = co2_sensor.getVoltage();
  double r = co2_sensor.getResistance();
  float r0 = co2_sensor.getR0();

  Serial.print("Analog Read: ");
  Serial.println(in);
  Serial.print("Voltage: ");
  Serial.println(v);
  Serial.print("Resistance: ");
  Serial.println(r);

  // Serial.print("Temperature: ");
  // Serial.println(temp);
  // Serial.print("Humidity: ");
  // Serial.println(humidity);
  Serial.print("R0: ");
  Serial.println(r0);

  Serial.println("-----------------------------");

  delay(1000);
}
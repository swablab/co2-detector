#include <Arduino.h>
#include <MQ135.h>
#include <SparkFunHTU21D.h>

#define PIN_MQ135 A0
#define PIN_NOISE 2
#define PIN_LED_GREEN 3
#define PIN_LED_GREEN2 4
#define PIN_LED_YELLOW 5
#define PIN_LED_YELLOW2 6
#define PIN_LED_RED 7
#define PIN_LED_RED2 8

MQ135 co2_sensor(PIN_MQ135);
HTU21D envSensor;

void setup() {
  Serial.begin(9600);

  co2_sensor.setR0(200);

  envSensor.begin();
}

void loop() {
  float temp = envSensor.readTemperature();
  float humidity = envSensor.readHumidity();

  float r0c = co2_sensor.getCorrectedR0(temp, humidity);
  float in = analogRead(PIN_MQ135);
  double v = co2_sensor.getVoltage();
  double r = co2_sensor.getResistance();
  float r0 = co2_sensor.getR0();

  double co2 = co2_sensor.getCO2();
  double co2c = co2_sensor.getCorrectedCO2(temp, humidity);

  Serial.print("Analog Read: ");
  Serial.println(in);
  Serial.print("Voltage: ");
  Serial.println(v);
  Serial.print("Resistance: ");
  Serial.println(r);

  Serial.print("R0: ");
  Serial.println(r0);
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("R0 Corrected: ");
  Serial.println(r0c);

  Serial.print("CO2: ");
  Serial.println(co2);
  Serial.print("CO2 Corrected: ");
  Serial.println(co2c);

  Serial.println("-----------------------------");

  delay(1000);
}
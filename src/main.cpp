#include <Arduino.h>
#include <MQ135.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define PIN_MQ135 A0
#define PIN_LED_GREEN DD2
#define PIN_LED_YELLOW DD3
#define PIN_LED_RED DD4
#define PIN_NOISE DD5

#define MEASURE_DELAY 1000
#define NOISE_DELAY 100

#define SEALEVELPRESSURE_HPA (1013.25)

MQ135 co2_sensor = MQ135(PIN_MQ135);
Adafruit_BME280 bme(10, 11, 12, 13);
const int maxCount = MEASURE_DELAY / NOISE_DELAY;
int count = -1;
float ppm = 0;
bool noise = false;

void setup() {
  pinMode(PIN_MQ135, INPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_NOISE, OUTPUT);

  Serial.begin(9600);

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
  }
}

void printValues(float ppm, float temp, float humidity);

void loop() {
  if (count >= maxCount || count < 0) {
    float temp = bme.readTemperature();
    float humidity = bme.readHumidity();
    ppm = co2_sensor.getCorrectedPPM(temp, humidity);
    
    count = 0;
    if (ppm < 1000) {
      digitalWrite(PIN_LED_GREEN, 1);
      digitalWrite(PIN_LED_YELLOW, 0);
      digitalWrite(PIN_LED_RED, 0);
    }
    else if (ppm <= 2000) {
      digitalWrite(PIN_LED_GREEN, 0);
      digitalWrite(PIN_LED_YELLOW, 1);
      digitalWrite(PIN_LED_RED, 0);
    }
    else {
      digitalWrite(PIN_LED_GREEN, 0);
      digitalWrite(PIN_LED_YELLOW, 0);
      digitalWrite(PIN_LED_RED, 1);
    }

    printValues(ppm, temp, humidity);
  }

  if (ppm > 2000) {
    noise = !noise;
    digitalWrite(PIN_NOISE, noise);
  }
  else {
    digitalWrite(PIN_NOISE, 0);
  }

  delay(NOISE_DELAY);
  count++;
}

void printValues(float ppm, float temp, float humidity) {
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" *C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print ("ppm = ");
  Serial.println (ppm);

  Serial.print ("rzero = ");
  Serial.println (co2_sensor.getCorrectedRZero(temp, humidity));

  Serial.println();
}
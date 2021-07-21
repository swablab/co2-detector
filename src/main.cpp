#include <Arduino.h>
#include <MQ135.h>
#include <SparkFunHTU21D.h>

#define PIN_MQ135 A7
#define PIN_NOISE 2
#define PIN_LED_GREEN 3
#define PIN_LED_GREEN2 4
#define PIN_LED_YELLOW 5
#define PIN_LED_YELLOW2 6
#define PIN_LED_RED 7
#define PIN_LED_RED2 8

void printValues(float ppm, float temp, float humidity);

const int maxCount = 10;
int count = 0;

bool noise = false;
bool noiseActive = false;

// loading
bool loading = true;
int firstRead;
const int loadingDelay = 200;
int loadingCount = 30000 / loadingDelay;

MQ135 co2_sensor(PIN_MQ135);
HTU21D envSensor;

void setup() {
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_GREEN2, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_YELLOW2, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_RED2, OUTPUT);
  pinMode(PIN_NOISE, OUTPUT);
  Serial.begin(9600);
  co2_sensor.setR0(200);

  // if (!bme.begin(0x76)) {
  //   Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
  // }
  envSensor.begin();
}

void loop() {
  if (loading) {
    if (loadingCount <= 0) {
      loading = false;
      count = -1;
      return;
    }

    int temp = analogRead(PIN_MQ135);
    if (temp > firstRead) {
      firstRead = temp;
    }
    else if (temp < (firstRead - 100) && loadingCount > 10) {
      loadingCount = 10;
    }

    digitalWrite(PIN_LED_GREEN, 0);
    digitalWrite(PIN_LED_GREEN2, 0);
    digitalWrite(PIN_LED_YELLOW, 0);
    digitalWrite(PIN_LED_YELLOW2, 0);
    digitalWrite(PIN_LED_RED, 0);
    digitalWrite(PIN_LED_RED2, 0);

    switch (count)
    {
      case 1:
        digitalWrite(PIN_LED_RED2, 1);
        break;
      case 2:
        digitalWrite(PIN_LED_RED, 1);
        digitalWrite(PIN_LED_RED2, 1);
        break;
      case 3:
        digitalWrite(PIN_LED_RED, 1);
        digitalWrite(PIN_LED_YELLOW2, 1);
        break;
      case 4:
        digitalWrite(PIN_LED_YELLOW2, 1);
        digitalWrite(PIN_LED_YELLOW, 1);
        break;
      case 5:
        digitalWrite(PIN_LED_YELLOW, 1);
        digitalWrite(PIN_LED_GREEN2, 1);
        break;
      case 6:
        digitalWrite(PIN_LED_GREEN2, 1);
        digitalWrite(PIN_LED_GREEN, 1);
        break;
      case 7:
        digitalWrite(PIN_LED_GREEN, 1);
        break;
      case 10:
        count = 0;
        break;
      
      default:
        break;
    }

    loadingCount--;
    count++;
    delay(loadingDelay);
    return;
  }

  if (count >= maxCount || count < 0) {
    float temp = envSensor.readTemperature();
    float humidity = envSensor.readHumidity();
    float ppm = co2_sensor.getCorrectedCO2(temp, humidity);
    
    count = 0;
    noiseActive = false;
    digitalWrite(PIN_LED_GREEN, 0);
    digitalWrite(PIN_LED_GREEN2, 0);
    digitalWrite(PIN_LED_YELLOW, 0);
    digitalWrite(PIN_LED_YELLOW2, 0);
    digitalWrite(PIN_LED_RED, 0);
    digitalWrite(PIN_LED_RED2, 0);

    if (ppm < 900) {
      digitalWrite(PIN_LED_GREEN, 1);
    }
    if (ppm > 750 && ppm < 1100) {
      digitalWrite(PIN_LED_GREEN2, 1);
    }
    if (ppm > 900 && ppm < 1900) {
      digitalWrite(PIN_LED_YELLOW, 1);
    }
    if (ppm > 1500 && ppm < 2200) {
      digitalWrite(PIN_LED_YELLOW2, 1);
    }
    if (ppm > 2000 && ppm < 2800) {
      digitalWrite(PIN_LED_RED, 1);
    }
    if (ppm > 2500) {
      digitalWrite(PIN_LED_RED2, 1);
    }
    if (ppm > 3000) {
      noiseActive = true;
    }

    printValues(ppm, temp, humidity);
  }

  if (noiseActive) {
    noise = !noise;
    digitalWrite(PIN_NOISE, noise);
  }
  else {
    digitalWrite(PIN_NOISE, 0);
  }

  delay(100);
  count++;
}

void printValues(float ppm, float temp, float humidity) {
  Serial.print("ppm: ");
  Serial.println(ppm);
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humidity);
}
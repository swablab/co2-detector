#include <Arduino.h>
#include <MQ135.h>
#include <dht.h>

#define PIN_MQ135 A0
#define PIN_DHT11 A1

#define PIN_LED_GREEN DD2
#define PIN_LED_YELLOW DD3
#define PIN_LED_RED DD4
#define PIN_NOISE DD5

MQ135 co2_sensor = MQ135(PIN_MQ135);
dht dht_sensor;
int count = 0;
float ppm = -1;
bool noise = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_MQ135, INPUT);
  pinMode(PIN_DHT11, INPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_NOISE, OUTPUT);
}

float measure() {
  Serial.print(RZERO);
  Serial.println("---------------------------");
  Serial.print("DHT:\t");
  int chk = dht_sensor.read11(PIN_DHT11);
  switch (chk)
  {
    case DHTLIB_OK:  
      Serial.print("OK,\t"); 
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      Serial.print("Checksum error,\t"); 
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.print("Time out error,\t"); 
      break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
      Serial.print("Unknown error,\t"); 
      break;
  }
  Serial.println();

  Serial.print ("temperature: ");
  Serial.println (dht_sensor.temperature);
  Serial.print ("humidity: ");
  Serial.println (dht_sensor.humidity);

  float val = analogRead(A0);
  Serial.print ("raw = ");
  Serial.println (val);
  float zero = co2_sensor.getCorrectedRZero(dht_sensor.temperature, dht_sensor.humidity);
  Serial.print ("rzero: ");
  Serial.println (zero);
  float ppm = co2_sensor.getCorrectedPPM(dht_sensor.temperature, dht_sensor.humidity);
  Serial.print ("ppm: ");
  Serial.println (ppm);
  return ppm;
}

void loop() {
  if (count >= 5 || ppm < 0) {
    ppm = measure();
    count = 0;
  }

  if (ppm < 1000) {
    digitalWrite(PIN_LED_GREEN, 1);
    digitalWrite(PIN_LED_YELLOW, 0);
    digitalWrite(PIN_LED_RED, 0);
    digitalWrite(PIN_NOISE, 0);
  }
  else if (ppm <= 2000) {
    digitalWrite(PIN_LED_GREEN, 0);
    digitalWrite(PIN_LED_YELLOW, 1);
    digitalWrite(PIN_LED_RED, 0);
    digitalWrite(PIN_NOISE, 0);
  }
  else {
    digitalWrite(PIN_LED_GREEN, 0);
    digitalWrite(PIN_LED_YELLOW, 0);
    digitalWrite(PIN_LED_RED, 1);
    noise = !noise;
    digitalWrite(PIN_NOISE, noise);
  }

  delay(100);
  count++;
}
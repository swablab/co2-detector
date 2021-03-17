#include <Arduino.h>
#include <MQ135.h>
#include <dht.h>

#define PIN_MQ135 A0
#define PIN_DHT11 A1

MQ135 co2_sensor = MQ135(PIN_MQ135);
dht dht_sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {
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

  delay(2000);
}
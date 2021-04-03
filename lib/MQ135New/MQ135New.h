#ifndef MQ135New_H
#define MQ135New_H

#include "Arduino.h"

#define RL 10
#define VIn 5
#define Resolution 1024

#define ATMOCO2 397.13

class MQ135 {
 private:
  uint8_t _pin;
  float R0;
  double getPPM(float a, float b);

 public:
  MQ135(uint8_t pin);
  double getAcetona();
  double getAlcohol();
  double getCO();
  double getCO2();
  double getNH4();
  double getTolueno();
  float getR0();
  void setR0(float r0);
  double getRS();
  double getVoltage();
};
#endif

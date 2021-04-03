#ifndef MQ135New_H
#define MQ135New_H

#include "Arduino.h"

#define RL 10
#define VIn 5
#define Resolution 1024

#define ATMOCO2 397.13

const double VStep = (double)VIn / (Resolution - 1);

class MQ135 {
 private:
  uint8_t _pin;
  float R0;

 public:
  MQ135(uint8_t pin);
  float getR0();
  double getR0By(float ppm, float a, float b);
  void setR0(float r0);
  
  double getVoltage();
  double getResistance();
  double getPPM(float a, float b);

  double getAcetona();
  double getAlcohol();
  double getCO();
  double getCO2();
  double getNH4();
  double getTolueno();
};
#endif

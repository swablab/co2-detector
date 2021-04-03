#include "MQ135New.h"

MQ135::MQ135(uint8_t pin) {
  _pin = pin;
}

double MQ135::getRS() {
    double voltage = getVoltage();
    double RS = (double)((double)(VIn * RL) / voltage) - RL;
    return RS;
}

double MQ135::getVoltage() {
    int value = analogRead(_pin);
    double voltage = (double)(value * VIn) / (double)(Resolution - 1);
    return voltage;
}

double MQ135::getPPM(float a, float b) {
    double ratio = getRS() / R0;
    double ppm = a * pow(ratio, b);
    return ppm;
}

double MQ135::getAcetona() {
    return getPPM(34.668, -3.369);
}

double MQ135::getAlcohol() {
    return getPPM(77.255, -3.18);
}

double MQ135::getCO2() {
    return getPPM(110.47, -2.862) + ATMOCO2;
}

double MQ135::getCO() {
    return getPPM(605.18, -3.937);
}

double MQ135::getNH4() {
    return getPPM(102.2, -2.473);
}

double MQ135::getTolueno() {
    return getPPM(44.947, -3.445);
}

float MQ135::getR0() {
    double r0 = getRS() / 3.6;
    return r0;
}

void MQ135::setR0(float r0) {
    R0 = r0;
}

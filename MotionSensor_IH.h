#ifndef MOTIONSENSOR_IH_H
#define MOTIONSENSOR_IH_H
#include <Arduino.h>

class MotionSensor_IH
{
  public:
    MotionSensor_IH(int motionPin, int laserPin);
    void begin();
    void checkMovement();
  private:
    int _motionPin;
    int _laserPin;
    int currentPinState = LOW;
    int previousPinState = LOW;
};
#endif
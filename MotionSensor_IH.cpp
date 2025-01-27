#include "Arduino.h"

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

MotionSensor_IH :: MotionSensor_IH(int motionPin, int laserPin)
{
  _motionPin = motionPin;
  _laserPin = laserPin;
}

void MotionSensor_IH :: begin()
{
  pinMode(_motionPin, INPUT);
  pinMode(_laserPin, OUTPUT);
}

void MotionSensor_IH :: checkMovement()
{
  previousPinState = currentPinState; 
  currentPinState = digitalRead(_motionPin);
  if (previousPinState == LOW && currentPinState == HIGH)
  {
    Serial.println("Motion detected!");
    digitalWrite(_laserPin, HIGH);
  }
  else
  if (previousPinState == HIGH && currentPinState == LOW)
  {
    Serial.println("Motion Stopped!");
    // turn on the alarm, light or activate a device . . . here
    digitalWrite(_laserPin, LOW);
  }
  
}
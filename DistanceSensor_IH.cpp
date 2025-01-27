#include "Arduino.h"
#include <SoftwareSerial.h>

class DistanceSensor_IH{
  public:
    DistanceSensor_IH(byte rxPin, byte txPin);
    void begin();
    void checkDistance(int degree);
    void recordDistance(int degree, float measurement);
  private:
    byte _rxPin;
    byte _txPin;
    int readings[9];
    int recordedDistance[10];
    int recordingIndex = 0;
    int recordingDirection = 1;
    const int HEADER = 0x59;
    SoftwareSerial* _serial;
};

DistanceSensor_IH :: DistanceSensor_IH(byte rxPin, byte txPin){
  _rxPin = rxPin;
  _txPin = txPin;
}

void DistanceSensor_IH :: begin(){
  if (NULL != _serial)
    {
        delete _serial;
    }
    _serial = new SoftwareSerial(_rxPin, _txPin);
    _serial->begin(115200);
    if(_serial->available())
    {
       _serial->println("Connected to Distance Sensor!");
    }
}

void DistanceSensor_IH :: recordDistance(int degree, float measurement){
  if(degree >= 90){
    recordingDirection = -1;
  } else if (degree <= 0){
    recordingDirection = 1;
  }
  if (degree % 9 == 0){
    recordedDistance[recordingIndex] = measurement;
    recordingIndex += recordingDirection;
  }
}

void DistanceSensor_IH :: checkDistance(int degree){
  _serial->listen();
  if (_serial->available())
  {
    if (_serial->read() == HEADER)
    {
      readings[0] = HEADER;
      if (_serial->read() == HEADER)
      {
        readings[1] = HEADER;
        for (int i = 2; i < 9; i++)
        {
          readings[i] = _serial->read();
        }
        //Sum of values in check
        int check = readings[0] + readings[1] + readings[2] + readings[3] + readings[4] + readings[5] + readings[6] + readings[7];
        
        if (readings[8] == (check & 0xff))
        {
          float dist = readings[2] + readings[3] * 256;
          //Serial.print("dist = ");
          //Serial.println(dist);
          recordDistance(degree, dist);
        }
      }
    }
  }
}
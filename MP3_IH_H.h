#ifndef MP3_IH_H
#define MP3_IH_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

class MP3_IH {
  public:
    MP3_IH(int pin1, int pin2, int pin3, int pin4);
    void begin();
    void play(int songIndex);
  private:
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;
};

#endif
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

MP3_IH :: MP3_IH(int pin1, int pin2, int pin3, int pin4) {
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
}

void MP3_IH::begin() {
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);
  pinMode(_pin4, OUTPUT);
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
  digitalWrite(_pin3, LOW);
  digitalWrite(_pin4, LOW);
}

void MP3_IH::play(int songIndex){
  digitalWrite(songIndex, HIGH);
  delay(500);
  digitalWrite(songIndex, LOW);
}
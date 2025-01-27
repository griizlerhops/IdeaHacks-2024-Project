#ifndef Servo_IH_H
#define Servo_IH_H
#include <Servo.h>
#include <Arduino.h>

class Servo_IH{
  public:
    Servo_IH(int pin, Servo myservo);
    void begin();
    void sentinel();
    void search();
    bool isHome = false;
    int getDegree();
  private:
    int _pin;
    Servo _servo;
    int degree = 0;
    int degreeDirection = 1;
    void goHome();
};

#endif
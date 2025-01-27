#include "Arduino.h"
#include <Servo.h>

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

Servo_IH :: Servo_IH(int pin, Servo myservo){
  _pin = pin;
  _servo = myservo;
}

int Servo_IH :: getDegree(){
  return degree;
}

void Servo_IH :: begin(){
  _servo.attach(_pin);
}

void Servo_IH :: sentinel(){
  if( isHome ) isHome = false;
  if (degree >= 90){
    degreeDirection = -1;
  } else if (degree <= 0){
    degreeDirection = 1;
  }
  degree += degreeDirection;
  //Serial.println(degree);
  _servo.write(degree);
  delay(15);
}

void Servo_IH :: goHome(){
  _servo.write(0);
}

void Servo_IH :: search(){
  goHome();
  isHome = true;
}
#include "Servo_IH.h"
#include <Servo.h>
#include "DistanceSensor_IH.h"
#include "MP3_IH.h"
#include "MotionSensor_IH.h"

const byte DistanceSenRxPin = 2;
const byte DistanceSenTxPin = 3;
const int MP3Pin1 = 5;
const int MP3Pin2 = 6;
const int MP3Pin3 = 7;
const int MP3Pin4 = 8;
const int motionPin = 4;
const int laserPin = 10;
const int greenLightPin = 11;
const int redLightPin = 12;
const int buttonPin = A1;
bool gameEnded = false;
unsigned long loopValue = 0UL;
unsigned long randomInterval = random(1000, 10000);
Servo myServo;
Servo_IH servo = Servo_IH(9, myServo);
DistanceSensor_IH distanceSen = DistanceSensor_IH(DistanceSenRxPin, DistanceSenTxPin);
MP3_IH myMp3 = MP3_IH(MP3Pin1,MP3Pin2,MP3Pin3,MP3Pin4);
MotionSensor_IH motionSen = MotionSensor_IH(motionPin, laserPin);
bool greenLightVoice = false;
bool redLightVoice = false;
bool lightState = false; //flase is Green Light, true is Red Light

void setup() {
  // put your setup code here, to run once:
  pinMode(greenLightPin, OUTPUT);
  pinMode(redLightPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  myMp3.begin();
  motionSen.begin();
  servo.begin();
  distanceSen.begin();
  Serial.begin(9600);
  myMp3.play(4);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonVal = digitalRead(buttonPin);
  Serial.println(buttonVal);
  if( buttonVal == 1 || gameEnded){
    digitalWrite(greenLightPin, HIGH);
    digitalWrite(redLightPin, HIGH);
    gameEnded = true;
  } else {
    if(loopValue++ >= randomInterval){
      lightState = !lightState;
      randomInterval = random( 16000000UL,  160000000UL);
      loopValue = 0UL;
    }
    if(!lightState){ //If green light is active
      digitalWrite(greenLightPin, HIGH);
      digitalWrite(redLightPin, LOW);
      if(!greenLightVoice){ //Check if Green light line has been said, if not play it
        myMp3.play(3);
        greenLightVoice = true;
        redLightVoice = false;
      }
    } else {
      digitalWrite(redLightPin, HIGH);
      digitalWrite(greenLightPin, LOW);
      if(!redLightVoice){ //Check if Red light line has been said, if not play it
        //Play Red Light audio
        myMp3.play(2);
        redLightVoice = true;
        greenLightVoice = false;
      }
    }
    motionSen.checkMovement();
    servo.sentinel();
    int currentDegree = servo.getDegree();
    distanceSen.checkDistance(currentDegree);
  }
}
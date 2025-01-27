#include "Arduino.h"
#include <SoftwareSerial.h>

const byte rxPinL = 2;
const byte txPinL = 3;
SoftwareSerial Serial_1 (rxPinL,txPinL);
int dist;
int strength;
float temperature;
int check;
int i;
int uart[9];
const int HEADER = 0x59;
float distanceMeters = 0;

void setup()
{
  //delay(1000);
  Serial.begin(9600);
  //delay(1000);
  Serial_1.begin(115200);
  //delay(1000);
}

String MessageBuffer = "";
String Message = "";

void loop()
{ 
  if (Serial_1.available())
  {
    if (Serial_1.read() == HEADER)
    {
      uart[0] = HEADER;
      if (Serial_1.read() == HEADER)
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)
        {
          uart[i] = Serial_1.read();
        }
        //Sum of values in check
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        
        if (uart[8] == (check & 0xff))
        {
          dist = uart[2] + uart[3] * 256;
          strength = uart[4] + uart[5] * 256;
          temperature = uart[6] + uart[7] * 256;
          temperature = (temperature/8) - 256;
          Serial.print('\n'); 
          Serial.print("dist = ");
          Serial.println(dist);
          delay(500);
          distanceMeters = (float)dist;
          distanceMeters = distanceMeters/100;
          Serial.println(distanceMeters);
          Serial.println(strength);
          Serial.println(temperature);
          delay(500);
        }
      }
    }
  }
}
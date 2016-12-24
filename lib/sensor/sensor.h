#ifndef SENSOR
#define SENSOR

#include "Arduino.h"

namespace sen{
  enum DISTANCE{
      FAR=50,
      NORMAL=25,
      CLOSE=10
    };


  class DistanceSensor{
  private:
    int trig;
    int echo;
    int distance;


  public:
      DistanceSensor(int trig_, int echo_):trig(trig_), echo(echo_), distance(0){}
      // Initialize Pins trigger: OUTPUT, echo: INPUT
      void init(){
        pinMode(trig, OUTPUT);
        pinMode(echo, INPUT);
      }

      void run(){
        // process
          digitalWrite(trig, LOW);
          delayMicroseconds(2);
          digitalWrite(trig, HIGH);
          delayMicroseconds(10);
          int duration = pulseIn(echo, HIGH);

          int cm = duration/29/2;
          if (cm>0){
            distance = cm;
          }
      }

      // Return the value of distance
      int getDistance(){
        return distance;
      }

  };
}
#endif /* end of include guard:  */

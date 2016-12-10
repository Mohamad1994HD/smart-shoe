#ifndef SENSOR
#define SENSOR

#include "Arduino.h"

namespace _sen_{
  enum DISTANCE{
      FAR=100,
      NORMAL=20,
      CLOSE=10
    };


  class Sensor{
  private:
    int trig;
    int echo;
    int distance;


  public:
      Sensor(int trig_, int echo_):trig(trig_), echo(echo_), distance(0){}

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

      int getDistance(){
        return distance;
      }

  };
}
#endif /* end of include guard:  */

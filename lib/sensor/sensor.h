#ifndef SENSOR
#define SENSOR

#include "Arduino.h"


typedef void (*callback)(int);


enum DIST{
  NORMAL = 30,
  CLOSE = 20,
  TOO_CLOSE = 10
};


class Sensor{
private:
  int trig;
  int echo;
  callback callback_;
  int distance;

public:
    Sensor(int trig_, int echo_):trig(trig_), echo(echo_), distance(0), callback_(NULL){}

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
          if(callback_){
            callback_(cm);
          }
        }
    }

    void setCallback(callback cback){
      callback_ = cback;
    }

};

#endif /* end of include guard:  */

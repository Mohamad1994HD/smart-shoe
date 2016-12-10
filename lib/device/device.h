#ifndef DEVICE
#define DEVICE

#include "Arduino.h"

namespace _dev_{
  enum PARAMETERS{
        LOW_VIB=300,
        MED_VIB=400,
        HIGH_VIB=500,
        NO_VIB=0
    };

  class Device{
  protected:
    int pin;

  public:
    Device(int p):pin(p){}
    void set_pin(int p){
      pin = p;
    }
    void init(){
      pinMode(pin, OUTPUT);
    };

    virtual void on(){};
    virtual void off(){};

    virtual void commit()=0;
  };

  class Vibrator:public Device{
  private:
    unsigned int speed;
    int *speeds;
    unsigned int index;
    unsigned int size;

  public:

    Vibrator(int p):Device(p), speed(-1), index(0), size(0),speeds(NULL){
    }

    void init_speedlst(int *lst, unsigned int sz=1){
      speeds = lst;
      size = sz;
    }

    void commit(){
      if(speed >= 0) analogWrite(this->pin, speed);
      else{
        if (speeds){
          analogWrite(this->pin, speeds[index]);
        }
      }
    }
    //
    void increment_speed(){
      index++;
      if (index >= size){index = 0;}
    }

    void setSpeed(int sp){
      speed = sp;
    }

    int getSpeed(){
      if (speed > 0) return speed;
      else return speeds[index];
    }
  };
}
#endif /* end of include guard:  */

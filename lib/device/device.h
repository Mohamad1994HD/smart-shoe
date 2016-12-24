#ifndef DEVICE
#define DEVICE

#include "Arduino.h"

namespace dev{


  class Device{
  protected:
    int pin;

  public:
    Device(int p):pin(p){}
    // Set the pin number
    void set_pin(int p){
      pin = p;
    }
    // Initialize the pin of the device
    void init(){
      pinMode(pin, OUTPUT);
    };

    virtual void on(){};
    virtual void off(){};

    virtual void commit()=0;
  };


  enum SPEEDS{
        LOW_VIB=400,
        MED_VIB=500,
        HIGH_VIB=700,
        NO_VIB=0
    };

    class Vibrator:public Device{
    private:
      unsigned int speed;

    public:

      Vibrator(int p):Device(p), speed(-1){}


      // Commit changes
      virtual void commit(){
        if(speed >= 0) analogWrite(this->pin, speed);
      }

      // Set the vibrator speed directly
      void setSpeed(int sp){
        speed = sp;
      }
      // return current speed
      int getSpeed(){
        return speed;
      }
    };

    class EnhanceVibrator:public Vibrator{
    private:

      int *speeds;
      unsigned int index;
      unsigned int size;
    public:

      EnhanceVibrator (int p):Vibrator(p),speeds(NULL), index(0), size(0){}

      void init_speedlst(int *lst, unsigned int sz=1){
        speeds = lst;
        size = sz;
      }

      void commit(){
        if (speeds){
            analogWrite(this->pin, speeds[index]);
        }
      }

      // Increment speed from speed list
      void increment_speed(){
        index++;
        if (index >= size){index = 0;}
      }
    };

}
#endif /* end of include guard:  */

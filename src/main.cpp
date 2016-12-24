#include "resources.h"


class Component{
private:
  dev::Vibrator *vibrator;
  sen::DistanceSensor *DistanceSensor;
  int _mode;

public:
  struct mode{
    enum md{NORMAL, INVERSE};
  };

  Component(dev::Vibrator *v, sen::DistanceSensor *s, int _mode=mode::md::NORMAL):
  vibrator(v), DistanceSensor(s),_mode(_mode){}


  void init(){
    DistanceSensor->init();
    vibrator->init();
  }

  void setMode(int mode_=mode::md::NORMAL){
      _mode = mode_;
  }

  int getDistance(){
    return this->DistanceSensor->getDistance();
  }

  void run(){
    DistanceSensor->run();

    int distance = DistanceSensor->getDistance();
      Serial.println(distance);
    if(distance <  sen::DISTANCE::CLOSE){
      // if normal mode high vibration, if inverse low vibration
      if (_mode == mode::md::INVERSE){
        vibrator->setSpeed(dev::SPEEDS::NO_VIB);
      }else{
        vibrator->setSpeed(dev::SPEEDS::HIGH_VIB);
      }
    }
    else if (distance < sen::DISTANCE::NORMAL){
        vibrator->setSpeed(dev::SPEEDS::MED_VIB);
    }
    else if (distance < sen::DISTANCE::FAR){
      // If normal mode low vibration, if inverse high vibraiton
      if(_mode == mode::md::INVERSE){
        vibrator->setSpeed(dev::SPEEDS::HIGH_VIB);
      }else{
        vibrator->setSpeed(dev::SPEEDS::LOW_VIB);
      }
    }else{
      vibrator->setSpeed(dev::SPEEDS::NO_VIB);
    }
    vibrator->commit();
  }
};

const int SIZE = 3;

// DistanceSensors MODIFY LATER
sen::DistanceSensor DistanceSensor1(8, 9);// FRONT
sen::DistanceSensor DistanceSensor2(A2, A3); // INV SENSOR
sen::DistanceSensor DistanceSensor3(A0, A1); // SIDE
// vibrators MODIFY LATER
dev::Vibrator vib1(7); // FRONT
dev::Vibrator vib2(5); // INV MOTOR
dev::Vibrator vib3(3); // SIDE
// Components MODIFY LATER
Component c1(&vib1, &DistanceSensor1);
Component c2(&vib2, &DistanceSensor2, Component::mode::md::INVERSE);
Component c3(&vib3, &DistanceSensor3);

//
Component components[SIZE] = {c1,c2,c3
  // Component(&vib1, &DistanceSensor1),
  // Component(&vib2, &DistanceSensor2, Component::mode::md::INVERSE),
  // Component(&vib1, &DistanceSensor3)
 };



void setup(){
    Serial.begin(9600);
    for (int i = 0; i < SIZE; i++){
      components[i].init();
      Serial.print("INIT ");
    }

    // vib1.setSpeed(dev::SPEEDS::MED_VIB);
    // vib2.setSpeed(dev::SPEEDS::MED_VIB);
    // vib3.setSpeed(dev::SPEEDS::MED_VIB);
    // vib1.commit();
    // vib2.commit();
    // vib3.commit();
}

unsigned int last_pass = 0;
unsigned int time_delay = 100;

void loop(){
  //
  unsigned int t = millis();


  if(t-last_pass > time_delay){
    for(int i=0; i<SIZE; i++){
      components[i].run();
      delay(time_delay);
    }

    last_pass = t;
   }

}
